#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "elements.h"
#include "parser.h"
#include "lua.h"
#include "debug.h"
#include "globalindex.h"

Object *sizing(Object *obj)
{
  int i;

  for (i = 0; obj->childs[i] != NULL; i++)
    sizing(obj->childs[i]);

  if (obj->type > 0 && obj->type < CAMERA)
    taglist[obj->type].sizerfunc(obj);

  return obj;
}

Object *parse(char *filename)
{
  FILE *file = fopen(filename, "r");
  while (fgetc(file) != '(');
  return sizing(parseFile(file, NULL));
}

int isLetter(char c) {
  if (c >= 'a' && c <= 'z' ||
      c >= 'A' && c <= 'Z')
    return 1;
  return 0;
}

char **parseProperties(FILE *file)
{
  char c;
  int listPos = 0,
    stringPos = 0;
  char **list = (char **)malloc(sizeof(char*) * 255);
  int state = 0;
  /* State:
     0 = wait for param
     1 = read param-name
     2 = read param-value 
  */
  
  
  for (c = fgetc(file); c != ')'; c = fgetc(file)) {
    switch (state) {
    case 0:
      if (isLetter(c)) {
	state = 1;
	list[listPos] = (char*) malloc(sizeof(char) * 255);
	list[listPos+1] = (char*) malloc(sizeof(char) * 255);
	list[listPos][0] = c;
	stringPos = 1;
      }
      break;
      
    case 1:
      switch (c) {
      case '=':
	if (fgetc(file) != '"') {
	  fprintf(stderr, "parameter value has to be in quotes\n");
	  exit(1);
	}
	list[listPos][stringPos] = '\0';
	stringPos = 0;
	listPos++;
	state = 2;
	break;
      default:
	list[listPos][stringPos++] = c;
	break;
      }
      break;
      
    case 2:
      switch (c) {
      case '"':
	list[listPos][stringPos] = '\0';
	stringPos = 0;
	listPos++;
	state = 0;
	break;
      default:
	list[listPos][stringPos++] = c;
	break;
      }
      break;
    }
  }
  list[listPos] = NULL;
  return list;
}

char *lookupList(char **list, char *key)
{
  int i;
  for (i = 0; list[i] != NULL; i+=2) {
    if (strcmp(list[i], key) == 0) {
      return list[i+1];
    }
  }

  return NULL;
}

Object *createObject(char *name, char **list)
{
  Object *obj;
  int i;

  obj = objectInit(list);

  for (i = 0; taglist[i].name != NULL; i++) {
    if (strcmp(name, taglist[i].name) == 0) 
      return taglist[i].initfunc(obj, list);
  }
    
  return obj;
}

Object *parseCode(FILE *file, Object *parent, char **propertyList)
{
  int brakets;
  FILE *tmp_out;
  int c;
  char *cname = lookupList(propertyList, "cname");
  if (cname == NULL)
    return NULL;

  DMSG("Found code object\n");

  tmp_out = fopen("_lua_tmp.lua", "w");

  fprintf(tmp_out, "function %s(id)\n", cname);

  DMSG("Read code object\n");

  for (c = fgetc(file); ; c = fgetc(file)) {
    if (c == '(')
      brakets++;
    if (c == ')') {
      if (brakets == 0)
	break;
      else
	brakets--;
    }
    fputc(c, tmp_out);
  }
  fprintf(tmp_out, "\nend\n");

  fclose(tmp_out);

  DMSG("Load code object from file\n");
  luaL_dofile(l, "_lua_tmp.lua");
}

Object *parseFile(FILE *file, Object *parent)
{
  /* State:
     0 = read tag name [ ]
     1 = wait for property list [(]
     2 = check new objects [(]
     3 = Read content if tag name is code
  */
  int state = 0;
  int c;
  char **propertyList;
  char *name = (char *) malloc(sizeof(char) * 255);
  int i = 0;
  int iChild = 0;
  Object **childs;
  childs = (Object **) malloc(sizeof(Object) * 255);
  Object *obj;

  for (c = fgetc(file); c != ')'; c = fgetc(file)) {
    switch (state) {
    case 0:
      switch (c) {
      case ' ':
	name[i] = '\0';
	state = 1;
	break;
      default:
	name[i++] = c;
	break;
      }
      break;

    case 1:
      switch (c) {
      case '(':
	propertyList = parseProperties(file);
	obj = createObject(name, propertyList);
	if (strcmp(name, "code") == 0)
	  state = 3;
	else
	  state = 2;
	break;
      }
      break;

    case 2:
      switch (c) {
      case '(':
	childs[iChild++] = parseFile(file, obj);
	childs[iChild] = NULL;
	break;
      }
      break;

    case 3:
      DMSG("Got code - search vor (\n");
      switch (c) {
      case '(':
	DMSG("Found\n");
	parseCode(file, obj, propertyList);
	state = 2;
	break;
      }
      break;
    }

  }

  obj->parent = parent;
  obj->childs = childs;

  insertGlobalIndex(obj);

  if (obj->onInit != NULL)
    execEvent(obj->onInit, obj);

  return obj;
}

void elemSetd(char *src, double *dst)
{
  char *buffer;

  buffer = lookupList(elemList, src);
  if (buffer != NULL)
    *dst = strtod(buffer, NULL);

}

void elemSets(char *src, char **dst)
{
  char *buffer;

  buffer = lookupList(elemList, src);
  if (buffer != NULL)
    *dst = buffer;
}


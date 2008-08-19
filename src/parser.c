/*
 * File parser.c
 *
 * lisp3d is the legal property of Simon Goller (neosam@gmail.com).
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "elements.h"
#include "parser.h"
#include "lua.h"
#include "debug.h"
#include "globalindex.h"
#include "misc.h"
#include "types.h"

Object *sizing(Object *obj)
{
	int i;
	
	for (i = 0; obj->childs[i] != NULL; i++)
		sizing(obj->childs[i]);
	
	if ((obj->type > 0 && obj->type < CAMERA | obj->type >= LASTELEM) &&
	    taglist[obj->type].sizerfunc != NULL)
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

char **parseProperties(char *name, FILE *file)
{
	char c;
	int listPos = 2,
		stringPos = 0;
	char **list = MALLOCN(char*, 255);
	int state = 0;
	/* State:
	   0 = wait for param
	   1 = read param-name
	   2 = read param-value 
	*/
	
	list[0] = "tagname";
	list[1] = name;
	
	for (c = fgetc(file); c != ')' || state == 2; c = fgetc(file)) {
		switch (state) {
		case 0:
			if (isLetter(c)) {
				state = 1;
				list[listPos] = MALLOCN(char, 255);
				list[listPos+1] = MALLOCN(char, 255);
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
	
	DMSG("Create object - create base object\n");
	
	obj = objectInit(list);
	
	DMSG("Create real object\n");
	
	
	for (i = 0; taglist[i].name != NULL; i++) {
		if (strcmp(name, taglist[i].name) == 0 &&
		    taglist[i].initfunc != NULL) 
			return taglist[i].initfunc(obj, list);
	}
	
#ifndef NDEBUG
	printf("DEBUG: Created Object %s with type %i\n", name, obj->type);
#endif
	DMSG("Object created\n");
	
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
	char *name = MALLOCN(char, 255);
	int i = 0;
	int iChild = 0;
	Object **childs;
	childs = MALLOCN(Object *, 255);
	Object *obj;
	
	DMSG("parse file\n");
	
	for (c = fgetc(file); c != ')'; c = fgetc(file)) {
		switch (state) {
		case 0:
			switch (c) {
			case ' ':
				name[i] = '\0';
				state = 1;
				DMSG("switch to state 1\n");
				break;
			default:
				name[i++] = c;
				break;
			}
			break;
			
		case 1:
			switch (c) {
			case '(':
				propertyList = parseProperties(name, file);
				obj = createObject(name, propertyList);
				if (strcmp(name, "code") == 0) {
					state = 3;
					DMSG("switch to state 3\n");
				}
				else {
					state = 2;
					DMSG("switch to state 2\n");
				}
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
	
	DMSG("Set parent and childs\n");
	obj->parent = parent;
	obj->childs = childs;
	
	DMSG("Insert into Global index\n");
	insertGlobalIndex(obj);
	
	if (obj->onInit != NULL)
		execEvent(obj->onInit, obj);
	
	DMSG("parsing finished\n");
	
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

void elemSetp(char *src, Point *dst)
{
	char *buffer;
	float x1, x2, x3;

	buffer = lookupList(elemList, src);

	if (buffer != NULL) {
		printf("Found a point %s %s\n", src, buffer);
		sscanf(buffer, "(%f %f %f)", &x1, &x2, &x3);
		dst->x = x1;
		dst->y = x2;
		dst->z = x3;
		printf("point: %f %f %f\n", x1, x2, x3);
	}
}

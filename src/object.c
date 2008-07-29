#include <stdio.h>
#include <stdlib.h>

#include "object.h"
#include "globalindex.h"
#include "parser.h"
#include "elements.h"
#include "debug.h"

Object *newObject()
{
  Object *object = (Object *) malloc(sizeof(Object));

  object->type = 0;
  
  object->name = NULL;
  object->nameID = 0;

  object->class = NULL;
  object->classID = 0;

  object->onInit = NULL;
  object->onDraw = NULL;

  object->width = 0.0;
  object->height = 0.0;
  object->depth = 0.0;

  object->minX = 0.0;
  object->maxX = 0.0;
  object->minY = 0.0;
  object->maxY = 0.0;
  object->minZ = 0.0;
  object->maxZ = 0.0;

  return object;
}

Object *objectInit(char **list)
{
  Object *object = newObject();

  elemList = list;

  elemSets("name", &object->name);
  elemSets("class", &object->class);
  elemSets("onDraw", &object->onDraw);
  elemSets("onInit", &object->onInit);

  elemSetd("minX", &object->minX);
  elemSetd("maxX", &object->maxX);
  elemSetd("minY", &object->minY);
  elemSetd("maxY", &object->maxY);
  elemSetd("minZ", &object->minZ);
  elemSetd("maxZ", &object->maxZ);
  elemSetd("width", &object->width);
  elemSetd("height", &object->height);
  elemSetd("depth", &object->depth);

  printf("Tagname: %s\n", lookupList(list, "tagname"));

  /* User defined objects */
  if (object->name != NULL) {
#ifndef NDEBUG
    printf("DEBUG: Create Usertag %s\n", object->name);
#endif
    registerTag(object->name,
		usertagInit, usertagDraw, usertagSizer, object);
    DMSG("User Tag created\n");
  }
    

  return object;
}


char *objGetName(int index)
{
  return getGlobalIndex(index)->name;
}

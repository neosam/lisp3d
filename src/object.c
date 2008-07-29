#include <stdio.h>
#include <stdlib.h>

#include "object.h"
#include "globalindex.h"
#include "parser.h"

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

  return object;
}


char *objGetName(int index)
{
  return getGlobalIndex(index)->name;
}

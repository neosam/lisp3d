#include <stdio.h>
#include <stdlib.h>

#include "object.h"
#include "globalindex.h"

Object *newObject(int type, 
		  Object *parent,
		  char *name, 
		  char *class)
{
  Object *object = (Object *) malloc(sizeof(Object));
  
  object->type = type;
  object->parent = parent;

  object->name = name;
  object->nameID = 0;

  object->class = class;
  object->classID = 0;

  return object;
}


char *objGetName(int index)
{
  return getGlobalIndex(index)->name;
}

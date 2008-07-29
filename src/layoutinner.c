#include <stdlib.h>

#include "layoutinner.h"
#include "elements.h"
#include "parser.h"
#include "graphics.h"

LayoutInner *newLayoutInner(Object *obj)
{
  LayoutInner *lay = (LayoutInner*) malloc(sizeof(LayoutInner));
  
  lay->obj = *obj;

  return lay;
}

Object *layoutInnerInit(Object *obj, char **list)
{
  LayoutInner *lay;
  obj->type = LAYOUT_INNER;
  lay = newLayoutInner(obj);
  return (Object *) lay;
}

void layoutInnerDraw(Object *obj)
{
  int i;
  for (i = 0; obj->childs[i] != NULL; i++)
    draw(obj->childs[i]); 
}

void layoutInnerSizer(Object *obj)
{
  int i;
  double minx, maxx,
    miny, maxy,
    minz, maxz;

  if (obj->childs[0] == NULL) {
    obj->minX = obj->minY = obj->minZ = 
      obj->maxX = obj->maxY = obj->maxZ = 
      obj->width = obj->height = obj->depth = 0.0;
    return;
  }
  
  minx = obj->childs[0]->minX;
  maxx = obj->childs[0]->maxX;

  miny = obj->childs[0]->minY;
  maxy = obj->childs[0]->maxY;

  minz = obj->childs[0]->minZ;
  maxz = obj->childs[0]->maxZ;

  for (i = 1; obj->childs[i] != NULL; i++) {
    minx = (obj->childs[i]->minX < minx)? obj->childs[i]->minX: minx;
    maxx = (obj->childs[i]->maxX > maxx)? obj->childs[i]->maxX: maxx;
    miny = (obj->childs[i]->minY < miny)? obj->childs[i]->minY: miny;
    maxy = (obj->childs[i]->maxY > maxy)? obj->childs[i]->maxY: maxy;
    minz = (obj->childs[i]->minZ < minz)? obj->childs[i]->minZ: minz;
    maxz = (obj->childs[i]->maxZ > maxz)? obj->childs[i]->maxZ: maxz;
  }

  obj->minX = minx;
  obj->maxX = maxx;
  obj->minY = miny;
  obj->maxY = maxy;
  obj->minZ = minz;
  obj->maxZ = maxz;
  obj->width = maxx - minx;
  obj->height = maxy - miny;
  obj->depth = maxz - minz;
}

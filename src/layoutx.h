#ifndef LAYOUTX_H
#define LAYOUTX_H

#include "object.h"

struct LayoutX {
  Object obj;
  double offsetx[255];
  double offsety[255];
  double offsetz[255];
  int childs;
};
typedef struct LayoutX LayoutX;

LayoutX *newLayoutX(Object *obj);
Object *layoutXInit(Object *obj, char **list);
void layoutXDraw(Object *obj);
void layoutXSizer(Object *obj);

#endif

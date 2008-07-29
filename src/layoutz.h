#ifndef LAYOUTZ_H
#define LAYOUTZ_H

#include "object.h"

struct LayoutZ {
  Object obj;
  double offsetx[255];
  double offsety[255];
  double offsetz[255];
  int childs;
};
typedef struct LayoutZ LayoutZ;

LayoutZ *newLayoutZ(Object *obj);
Object *layoutZInit(Object *obj, char **list);
void layoutZDraw(Object *obj);
void layoutZSizer(Object *obj);

#endif

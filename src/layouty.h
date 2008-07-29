#ifndef LAYOUTY_H
#define LAYOUTY_H

#include "object.h"

struct LayoutY {
  Object obj;
  double offsetx[255];
  double offsety[255];
  double offsetz[255];
  int childs;
};
typedef struct LayoutY LayoutY;

LayoutY *newLayoutY(Object *obj);
Object *layoutYInit(Object *obj, char **list);
void layoutYDraw(Object *obj);
void layoutYSizer(Object *obj);

#endif

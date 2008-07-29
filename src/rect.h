#ifndef RECT_H
#define RECT_H

#include "object.h"

struct Rect {
  Object obj;

  double x1, y1, z1;
  double x2, y2, z2;
  double x3, y3, z3;
  double x4, y4, z4;
  double r, g, b;
};
typedef struct Rect Rect;

Rect *newRect(Object *obj);
Object *rectInit(Object *obj, char **list);
void rectDraw(Object *obj);
void rectSizer(Object *obj);

#endif

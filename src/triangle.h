#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "object.h"

/* Quad object */
struct Triangle {
  Object obj;

  /* vertex */
  double x1, y1, z1;
  double x2, y2, z2;
  double x3, y3, z3;
  double r, g, b;
};
typedef struct Triangle Triangle;

Triangle *newTriangle(Object *obj);
Triangle *triangleInit(Object *obj, char **list);
void triangleDraw(Triangle *tri);

/* Commands for global index */
double *triangleGetRGB(int index);
void triangleSetRGB(int index, double r, double g, double b);


#endif

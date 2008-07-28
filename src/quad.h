#ifndef QUAD_H
#define QUAD_H

#include "object.h"

/* Quad object */
struct Quad {
  Object obj;

  /* Dimensions */
  double sizeX, sizeY, sizeZ;
  int r, g, b;
};
typedef struct Quad Quad;

Quad *newQuad(Object *obj, double sizeX, double sizeY, double sizeZ);

void quadDraw(Quad *quad);

/* Commands for global index */
double *quadGetRGB(int index);
void quadSetRGB(int index, double r, double g, double b);


#endif

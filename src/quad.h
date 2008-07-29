#ifndef QUAD_H
#define QUAD_H

#include "object.h"

/* Quad object */
struct Quad {
  Object obj;

  /* Dimensions */
  double sizeX, sizeY, sizeZ;
  double r, g, b;
};
typedef struct Quad Quad;

Quad *newQuad(Object *obj);
Object *quadInit(Object *obj, char **list);
void quadDraw(Object *obj);
void quadSizer(Object *obj);

/* Commands for global index */
double *quadGetRGB(int index);
void quadSetRGB(int index, double r, double g, double b);


#endif

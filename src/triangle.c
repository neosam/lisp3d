#include <stdlib.h>
#include <stdio.h>
#include <SDL_opengl.h>

#include "triangle.h"
#include "globalindex.h"
#include "parser.h"
#include "debug.h"

Triangle *newTriangle(Object *obj)
{
  Triangle *tri = (Triangle *) realloc(obj, sizeof(Triangle));

  tri->x1 = 0.0;
  tri->x2 = 0.0;
  tri->x3 = 0.0;
  tri->y1 = 0.0;
  tri->y2 = 0.0;
  tri->y3 = 0.0;
  tri->z1 = 0.0;
  tri->z2 = 0.0;
  tri->z3 = 0.0;


  tri->r = 0.0;
  tri->g = 0.0;
  tri->b = 0.0;

  return tri;
}

void triangleCreateVertices(Triangle *tri)
{
  Object *obj = (Object*) tri;
  GLdouble r = tri->r,
    g = tri->g,
    b = tri->b;
  int p1 = objRegisterVertexc(obj, tri->x1, tri->y1, tri->z1, r, g, b),
    p2 = objRegisterVertexc(obj, tri->x2, tri->y2, tri->z2, r, g, b),
    p3 = objRegisterVertexc(obj, tri->x3, tri->y3, tri->z3, r, g, b);

  objAddFace(obj, p1, p2, p3);

  assert(obj->ventries == 3);
  assert(obj->fentries == 1);
}

Object *triangleInit(Object *obj, char **list)
{
  obj->type = TRIANGLE;
  Triangle *dst = newTriangle(obj);
  elemList = list;

  elemSetd("x1", &dst->x1);
  elemSetd("y1", &dst->y1);
  elemSetd("z1", &dst->z1);
  elemSetd("x2", &dst->x2);
  elemSetd("y2", &dst->y2);
  elemSetd("z2", &dst->z2);
  elemSetd("x3", &dst->x3);
  elemSetd("y3", &dst->y3);
  elemSetd("z3", &dst->z3);
  elemSetd("r", &dst->r);
  elemSetd("g", &dst->g);
  elemSetd("b", &dst->b);

  triangleCreateVertices(dst);

  return (Object *)dst;
}


double *triangleGetRGB(int index)
{
  double *res = (double*) malloc(sizeof(double)*3);
  Triangle *tri = (Triangle *)getGlobalIndex(index);

  res[0] = tri->r;
  res[1] = tri->g;
  res[2] = tri->b;

  return res;
}


void triangleSetRGB(int index, double r, double g, double b)
{
  Triangle *tri = (Triangle *)getGlobalIndex(index);
  
  tri->r = r;
  tri->g = g;
  tri->b = b;
}

#include <stdlib.h>
#include <stdio.h>
#include <SDL_opengl.h>

#include "triangle.h"
#include "globalindex.h"
#include "parser.h"

Triangle *newTriangle(Object *obj)
{
  Triangle *tri = (Triangle *) malloc(sizeof(Triangle));

  tri->obj = *obj;

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

  return (Object *)dst;
}


void triangleDraw(Object *obj)
{
  Triangle *tri = (Triangle *)obj;
  
  glBegin(GL_TRIANGLES);
  glColor3f(tri->r, tri->g, tri->b);

  glVertex3f(tri->x1, tri->y1, tri->z1);
  glVertex3f(tri->x2, tri->y2, tri->z2);
  glVertex3f(tri->x3, tri->y3, tri->z3);
  
  glEnd();
}

void triangleSizer(Object *obj)
{
  Triangle *tri = (Triangle*) obj;

  double minBuffer = tri->x1, 
    maxBuffer = tri->x1;

  if (tri->x2 < minBuffer)
    minBuffer = tri->x2;
  else
    maxBuffer = tri->x2;

  obj->minX = (minBuffer < tri->x3)? minBuffer: tri->x3;
  obj->maxX = (maxBuffer > tri->x3)? maxBuffer: tri->x3;

  minBuffer = tri->y1;
  maxBuffer = tri->y1;

  if (tri->y2 < minBuffer)
    minBuffer = tri->y2;
  else
    maxBuffer = tri->y2;

  obj->minY = (minBuffer < tri->y3)? minBuffer: tri->y3;
  obj->maxY = (maxBuffer > tri->y3)? maxBuffer: tri->y3;

  minBuffer = tri->z1;
  maxBuffer = tri->z1;

  if (tri->z2 < minBuffer)
    minBuffer = tri->z2;
  else
    maxBuffer = tri->z2;

  obj->minZ = (minBuffer < tri->z3)? minBuffer: tri->z3;
  obj->maxZ = (maxBuffer > tri->z3)? maxBuffer: tri->z3;

  obj->width = obj->maxX - obj->minX;
  obj->height = obj->maxY - obj->minY;
  obj->depth = obj->maxZ - obj->minZ;
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

  printf("%i %f %f %f\n", index, r, g, b);
}

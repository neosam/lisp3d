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

  return tri;
}

char **elemList;

void elemSetd(char *src, double *dst)
{
  char *buffer;

  buffer = lookupList(elemList, src);
  if (buffer != NULL)
    *dst = strtod(buffer, NULL);

}

Triangle *triangleInit(Object *obj, char **list)
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

  return dst;
}


void triangleDraw(Triangle *tri)
{
  glBegin(GL_TRIANGLES);
  glColor3f(tri->r, tri->g, tri->b);

  glVertex3f(tri->x1, tri->y1, tri->z1);
  glVertex3f(tri->x2, tri->y2, tri->z2);
  glVertex3f(tri->x3, tri->y3, tri->z3);
  
  glEnd();
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

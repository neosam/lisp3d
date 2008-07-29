#include <stdlib.h>
#include <stdio.h>
#include <SDL_opengl.h>

#include "quad.h"
#include "globalindex.h"
#include "parser.h"

Quad *newQuad(Object *obj)
{
  Quad *quad = (Quad *) malloc(sizeof(Quad));

  quad->obj = *obj;

  quad->sizeX = 0.0;
  quad->sizeY = 0.0;
  quad->sizeZ = 0.0;

  return quad;
}

Object *quadInit(Object *obj, char **list)
{
  Quad *quad;
  obj->type = QUAD;
  quad = newQuad(obj);
  elemList = list;
  
  elemSetd("sizeX", &quad->sizeX);
  elemSetd("sizeY", &quad->sizeY);
  elemSetd("sizeZ", &quad->sizeZ);
  elemSetd("r", &quad->r);
  elemSetd("g", &quad->g);
  elemSetd("b", &quad->b);
  
  return (Object*) quad;
}

void quadDraw(Object *obj)
{
  Quad *quad = (Quad*) obj;
  glBegin(GL_QUADS);
  // Front
  glColor3f(quad->r, quad->g, quad->b);
  glVertex3f( quad->sizeX/2,  quad->sizeY/2, quad->sizeZ/2);
  glVertex3f(-quad->sizeX/2,  quad->sizeY/2, quad->sizeZ/2);
  glVertex3f(-quad->sizeX/2, -quad->sizeY/2, quad->sizeZ/2);
  glVertex3f( quad->sizeX/2, -quad->sizeY/2, quad->sizeZ/2);

  glVertex3f( quad->sizeX/2,  quad->sizeY/2, -quad->sizeZ/2);
  glVertex3f(-quad->sizeX/2,  quad->sizeY/2, -quad->sizeZ/2);
  glVertex3f(-quad->sizeX/2, -quad->sizeY/2, -quad->sizeZ/2);
  glVertex3f( quad->sizeX/2, -quad->sizeY/2, -quad->sizeZ/2);

  // Side
  glVertex3f( quad->sizeX/2,  quad->sizeY/2,  quad->sizeZ/2);
  glVertex3f( quad->sizeX/2,  quad->sizeY/2, -quad->sizeZ/2);
  glVertex3f(-quad->sizeX/2,  quad->sizeY/2, -quad->sizeZ/2);
  glVertex3f(-quad->sizeX/2,  quad->sizeY/2,  quad->sizeZ/2);

  glVertex3f( quad->sizeX/2,  -quad->sizeY/2,  quad->sizeZ/2);
  glVertex3f( quad->sizeX/2,  -quad->sizeY/2, -quad->sizeZ/2);
  glVertex3f(-quad->sizeX/2,  -quad->sizeY/2, -quad->sizeZ/2);
  glVertex3f(-quad->sizeX/2,  -quad->sizeY/2,  quad->sizeZ/2);

  // Topdown
  glVertex3f( quad->sizeX/2,  quad->sizeY/2,  quad->sizeZ/2);
  glVertex3f( quad->sizeX/2, -quad->sizeY/2,  quad->sizeZ/2);
  glVertex3f( quad->sizeX/2, -quad->sizeY/2, -quad->sizeZ/2);
  glVertex3f( quad->sizeX/2,  quad->sizeY/2, -quad->sizeZ/2);

  glVertex3f(-quad->sizeX/2,  quad->sizeY/2,  quad->sizeZ/2);
  glVertex3f(-quad->sizeX/2, -quad->sizeY/2,  quad->sizeZ/2);
  glVertex3f(-quad->sizeX/2, -quad->sizeY/2, -quad->sizeZ/2);
  glVertex3f(-quad->sizeX/2,  quad->sizeY/2, -quad->sizeZ/2);


  
  glEnd();
}

void quadSizer(Object *obj)
{
  Quad *quad = (Quad*) obj;

  obj->minX = -quad->sizeX/2;
  obj->minY = -quad->sizeY/2;
  obj->minZ = -quad->sizeZ/2;

  obj->maxX = quad->sizeX/2;
  obj->maxY = quad->sizeY/2;
  obj->maxZ = quad->sizeZ/2;
  
  obj->width = quad->sizeX;
  obj->height = quad->sizeY;
  obj->depth = quad->sizeZ;
}



double *quadGetRGB(int index)
{
  double *res = (double*) malloc(sizeof(double)*3);
  Quad *quad = (Quad *)getGlobalIndex(index);

  res[0] = quad->r;
  res[1] = quad->g;
  res[2] = quad->b;

  return res;
}


void quadSetRGB(int index, double r, double g, double b)
{
  Quad *quad = (Quad *)getGlobalIndex(index);
  
  quad->r = r;
  quad->g = g;
  quad->b = b;
}

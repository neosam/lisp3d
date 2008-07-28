#include <stdlib.h>
#include <stdio.h>
#include <SDL_opengl.h>

#include "quad.h"
#include "globalindex.h"

Quad *newQuad(Object *obj, double sizeX, double sizeY, double sizeZ)
{
  Quad *quad = (Quad *) malloc(sizeof(Quad));

  quad->obj = *obj;

  quad->sizeX = sizeX;
  quad->sizeY = sizeY;
  quad->sizeZ = sizeZ;

  return quad;
}

void quadDraw(Quad *quad)
{
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

  printf("%i %f %f %f\n", index, r, g, b);
}

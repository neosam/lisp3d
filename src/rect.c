#include <stdlib.h>
#include <SDL_opengl.h>

#include "rect.h"
#include "parser.h"
#include "elements.h"

Rect *newRect(Object *obj)
{
  Rect *rect = (Rect*) malloc(sizeof(Rect));

  rect->obj = *obj;

  rect->x1 = 0.0;
  rect->x2 = 0.0;
  rect->x3 = 0.0;
  rect->x4 = 0.0;

  rect->y1 = 0.0;
  rect->y2 = 0.0;
  rect->y3 = 0.0;
  rect->y4 = 0.0;

  rect->z1 = 0.0;
  rect->z2 = 0.0;
  rect->z3 = 0.0;
  rect->z4 = 0.0;
  
  rect->r = 0.0;
  rect->g = 0.0;
  rect->b = 0.0;

  return rect;
}

Object *rectInit(Object *obj, char **list)
{
  Rect *rect;
  
  obj->type = RECT;
  rect = newRect(obj);
  elemList = list;

  elemSetd("x1", &rect->x1);
  elemSetd("x2", &rect->x2);
  elemSetd("x3", &rect->x3);
  elemSetd("x4", &rect->x4);

  elemSetd("y1", &rect->y1);
  elemSetd("y2", &rect->y2);
  elemSetd("y3", &rect->y3);
  elemSetd("y4", &rect->y4);

  elemSetd("z1", &rect->z1);
  elemSetd("z2", &rect->z2);
  elemSetd("z3", &rect->z3);
  elemSetd("z4", &rect->z4);

  elemSetd("r", &rect->r);
  elemSetd("g", &rect->g);
  elemSetd("b", &rect->b);

  return (Object *) rect;
}

void rectDraw(Object *obj)
{
  Rect *rect = (Rect*) obj;

  glBegin(GL_QUADS);
  glColor3f(rect->r, rect->g, rect->b);
  glVertex3f(rect->x1, rect->y1, rect->z1);
  glVertex3f(rect->x2, rect->y2, rect->z2);
  glVertex3f(rect->x3, rect->y3, rect->z3);
  glVertex3f(rect->x4, rect->y4, rect->z4);
  glEnd();
}

void rectSizer(Object *obj)
{
  Rect *rect = (Rect*) obj;

  double minBuffer = rect->x1, 
    maxBuffer = rect->x1;

  if (rect->x2 < minBuffer)
    minBuffer = rect->x2;
  else
    maxBuffer = rect->x2;

  minBuffer = (minBuffer < rect->x3)? minBuffer: rect->x3;
  maxBuffer = (maxBuffer > rect->x3)? maxBuffer: rect->x3;

  obj->minX = (minBuffer < rect->x4)? minBuffer: rect->x4;
  obj->maxX = (maxBuffer > rect->x4)? maxBuffer: rect->x4;

  minBuffer = rect->y1;
  maxBuffer = rect->y1;

  if (rect->y2 < minBuffer)
    minBuffer = rect->y2;
  else
    maxBuffer = rect->y2;

  minBuffer = (minBuffer < rect->y3)? minBuffer: rect->y3;
  maxBuffer = (maxBuffer > rect->y3)? maxBuffer: rect->y3;

  obj->minY = (minBuffer < rect->y4)? minBuffer: rect->y4;
  obj->maxY = (maxBuffer > rect->y4)? maxBuffer: rect->y4;

  minBuffer = rect->z1;
  maxBuffer = rect->z1;

  if (rect->z2 < minBuffer)
    minBuffer = rect->z2;
  else
    maxBuffer = rect->z2;

  minBuffer = (minBuffer < rect->z3)? minBuffer: rect->z3;
  maxBuffer = (maxBuffer > rect->z3)? maxBuffer: rect->z3;

  obj->minZ = (minBuffer < rect->z4)? minBuffer: rect->z4;
  obj->maxZ = (maxBuffer > rect->z4)? maxBuffer: rect->z4;

  obj->width = obj->maxX - obj->minX;
  obj->height = obj->maxY - obj->minY;
  obj->depth = obj->maxZ - obj->minZ;

}

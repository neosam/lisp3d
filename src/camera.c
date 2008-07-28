#include <stdio.h>
#include <stdlib.h>
#include <SDL_opengl.h>

#include "camera.h"
#include "globalindex.h"
#include "parser.h"

Camera *cam;

Camera *newCamera(Object *obj)
{
  Camera *result = (Camera *) malloc(sizeof(Camera));

  result->obj = *obj;

  result->x = 0.0;
  result->y = 0.0;
  result->z = 0.0;
  
  result->frontX = 0.0;
  result->frontY = 0.0;
  result->frontZ = -1.0;

  result->upX = 0.0;
  result->upY = 1.0;
  result->upZ = 0.0;

  result->fovy = 60.0;
  result->aspect = 1.33333;
}

Camera *cameraInit(Object *obj, char **list)
{
  obj->type = CAMERA;
  Camera *dst = newCamera(obj);
  char *buffer;

  buffer = lookupList(list, "x");
  if (buffer != NULL)
    dst->x = strtod(buffer, NULL);
  buffer = lookupList(list, "y");
  if (buffer != NULL)
    dst->y = strtod(buffer, NULL);
  buffer = lookupList(list, "z");
  if (buffer != NULL)
    dst->z = strtod(buffer, NULL);

  buffer = lookupList(list, "frontX");
  if (buffer != NULL)
    dst->frontX = strtod(buffer, NULL);
  buffer = lookupList(list, "frontY");
  if (buffer != NULL)
    dst->frontY = strtod(buffer, NULL);
  buffer = lookupList(list, "frontZ");
  if (buffer != NULL)
    dst->frontZ = strtod(buffer, NULL);

  buffer = lookupList(list, "upX");
  if (buffer != NULL)
    dst->upX = strtod(buffer, NULL);
  buffer = lookupList(list, "upY");
  if (buffer != NULL)
    dst->upY = strtod(buffer, NULL);
  buffer = lookupList(list, "upZ");
  if (buffer != NULL)
    dst->upZ = strtod(buffer, NULL);

  buffer = lookupList(list, "fovy");
  if (buffer != NULL)
    dst->fovy = strtod(buffer, NULL);
  buffer = lookupList(list, "aspect");
  if (buffer != NULL)
    dst->aspect = strtod(buffer, NULL);


  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(dst->fovy, dst->aspect, 0.1, 100.0);
  glMatrixMode(GL_MODELVIEW);

  cam = dst;

  return dst;
}

#ifndef CAMERA_H
#define CAMERA_H

#include "object.h"

struct Camera
{
  Object obj;

  /* Position */
  double x, y, z;
  double frontX, frontY, frontZ;
  double upX, upY, upZ;

  double fovy, aspect;
};
typedef struct Camera Camera;

extern Camera *cam;

Camera *newCamera(Object *obj);
Camera *cameraInit(Object *obj, char **list);

#endif

/* OBJECT
 * +QUAD
 * +CODE
 */

#ifndef ELEMENTS_H
#define ELEMENTS_H

#include "object.h"
#include "quad.h"
#include "camera.h"
#include "triangle.h"
#include "rect.h"
#include "layoutinner.h"
#include "layoutx.h"

#define CQUAD(x) ((Quad*)(x))

struct _tags {
  char *name;
  Object *(*initfunc)(Object *obj, char **list);
  void (*drawfunc)(Object *obj);
  void (*sizerfunc)(Object *obj);
};

extern struct _tags taglist[];


/* Build in types */
enum ObjType {
  OBJECT = 0,
  QUAD,
  TRIANGLE,
  RECT,
  LAYOUT_INNER,
  LAYOUT_X,
  CAMERA,
  CODE,
  LASTELEM
};





#endif

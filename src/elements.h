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
#include "layouty.h"
#include "layoutz.h"
#include "usertag.h"

#define CQUAD(x) ((Quad*)(x))

struct _tags {
  char *name;
  Object *(*initfunc)(Object *obj, char **list);
  void (*drawfunc)(Object *obj);
  void (*sizerfunc)(Object *obj);
  Object *ref;
};

extern struct _tags *taglist;


/* Build in types */
enum ObjType {
  OBJECT = 0,
  QUAD,
  TRIANGLE,
  RECT,
  LAYOUT_INNER,
  LAYOUT_X,
  LAYOUT_Y,
  LAYOUT_Z,
  CAMERA,
  CODE,
  LASTELEM
};

void registerTag(char *name, Object*(*initfunc)(Object *obj, char **list),
		 void (*drawfunc)(Object *obj), 
		 void (*sizerfunc)(Object *obj), Object *ref);

void initElements();

#endif

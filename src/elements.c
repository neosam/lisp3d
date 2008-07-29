#include <stdlib.h>
#include <stdio.h>

#include "elements.h"
#include "globalindex.h"


/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1111
   taglist must be in the same order as enum ObjType in elements.h
   If not, the wrong object will be drawn ;)  */

/* order: {tagname(char*), init-function, draw-function}
initfunction is from type: Object *initFunc(Object *obj, char **list)
drawfunction is from type: void drawFunc(Object *obj) */

struct _tags taglist[] = {
  {"object", NULL, NULL, NULL},
  {"quad", quadInit, quadDraw, quadSizer},
  {"triangle", triangleInit, triangleDraw, triangleSizer},
  {"rect", rectInit, rectDraw, rectSizer},
  {"layout-inner", layoutInnerInit, layoutInnerDraw, layoutInnerSizer},
  {"layout-x", layoutXInit, layoutXDraw, layoutXSizer},
  {"camera", cameraInit, cameraDraw, NULL},
  {NULL, NULL, NULL}}; /* Last must be null */


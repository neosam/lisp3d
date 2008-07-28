/* OBJECT
 * +QUAD
 * +CODE
 */

#ifndef ELEMENTS_H
#define ELEMENTS_H

#include "object.h"
#include "quad.h"
#include "camera.h"

#define CQUAD(x) ((Quad*)(x))


/* Build in types */
enum ObjType {
  OBJECT,
  DRAW_OBJECT,
  QUAD,
  CAMERA,
  CODE,
  LASTELEM
};





#endif

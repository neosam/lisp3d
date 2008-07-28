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

#define CQUAD(x) ((Quad*)(x))


/* Build in types */
enum ObjType {
  OBJECT,
  DRAW_OBJECT,
  QUAD,
  TRIANGLE,
  CAMERA,
  CODE,
  LASTELEM
};





#endif

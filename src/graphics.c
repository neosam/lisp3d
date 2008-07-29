#include <stdlib.h>

#include "graphics.h"
#include "elements.h"

void draw(Object *obj) {
  int i;

  if (obj->onDraw != NULL)
    execEvent(obj->onDraw, obj);

  if (obj->type > 0 && obj->type < CAMERA)
    taglist[obj->type].drawfunc(obj);

  /*  for (i = 0; obj->childs[i] != NULL; i++)
      draw(obj->childs[i]); */
}

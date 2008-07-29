#include <stdlib.h>
#include <stdio.h>
#include <SDL_opengl.h>

#include "layoutz.h"
#include "elements.h"
#include "parser.h"
#include "graphics.h"

LayoutZ *newLayoutZ(Object *obj)
{
  LayoutZ *lay = (LayoutZ*) malloc(sizeof(LayoutZ));
  
  lay->obj = *obj;

  return lay;
}

Object *layoutZInit(Object *obj, char **list)
{
  LayoutZ *lay;
  obj->type = LAYOUT_Z;
  lay = newLayoutZ(obj);
  return (Object *) lay;
}

void layoutZDraw(Object *obj)
{
  int i;
  LayoutZ *lay = (LayoutZ*) obj;
  
  for (i = 0; obj->childs[i] != NULL; i++) {
    glPushMatrix();
    glTranslatef(lay->offsetx[i],
		 lay->offsety[i],
		 lay->offsetz[i]);
    draw(obj->childs[i]); 
    glPopMatrix();
  }
}

void layoutZSizer(Object *obj)
{
  int i;
  double width, height, depth;
  LayoutZ *lay = (LayoutZ*) obj;

  if (obj->childs[0] == NULL) {
    printf("Layout: no objects\n");
    obj->minX = obj->minY = obj->minZ = 
      obj->maxX = obj->maxY = obj->maxZ = 
      obj->width = obj->height = obj->depth = 0.0;
    return;
  }
  
  width = obj->childs[0]->width;
  height = obj->childs[0]->height;
  depth = obj->childs[0]->depth;

  for (i = 1; obj->childs[i] != NULL; i++) {
    height = (obj->childs[i]->height > height)? obj->childs[i]->height: height;
    width = (obj->childs[i]->width > width)? obj->childs[i]->width: width;
    depth += obj->childs[i]->depth;
  }

  printf("Layout: %i\n", i);

  obj->minX = -width/2;
  obj->maxX = width/2;
  obj->minY = -height/2;
  obj->maxY = height/2;
  obj->minZ = -depth/2;
  obj->maxZ = depth/2;
  obj->width = width;
  obj->height = height;
  obj->depth = depth;
  lay->childs = i;

  /* Layouting */
  depth = -depth/2;
  for (i = 0; i < lay->childs; i++) {
    lay->offsetz[i] = -(obj->childs[i]->maxZ + obj->childs[i]->minZ) / 2 + 
      depth + obj->childs[i]->depth/2;
    printf("%f\n", lay->offsetx[i]);
    lay->offsety[i] = -(obj->childs[i]->maxY + obj->childs[i]->minY) / 2;
    lay->offsetx[i] = -(obj->childs[i]->maxX + obj->childs[i]->minX) / 2;
    depth += obj->childs[i]->depth;
  }
}

#include <stdlib.h>
#include <stdio.h>
#include <SDL_opengl.h>

#include "layoutx.h"
#include "elements.h"
#include "parser.h"
#include "graphics.h"
#include "misc.h"

LayoutX *newLayoutX(Object *obj)
{
	LayoutX *lay = REALLOC(LayoutX, obj);
	
	return lay;
}

Object *layoutXInit(Object *obj, char **list)
{
	LayoutX *lay;
	obj->type = LAYOUT_X;
	lay = newLayoutX(obj);
	return (Object *) lay;
}

void layoutXDraw(Object *obj)
{
	int i;
	LayoutX *lay = (LayoutX*) obj;
	
	for (i = 0; obj->childs[i] != NULL; i++) {
		glPushMatrix();
		glTranslatef(lay->offsetx[i], lay->offsety[i], 
                                                           lay->offsetz[i]);
		draw(obj->childs[i]); 
		glPopMatrix();
	}
}

void layoutXSizer(Object *obj)
{
	int i;
	double width, height, depth;
	LayoutX *lay = (LayoutX*) obj;
	
	if (obj->childs[0] == NULL) {
		obj->minX = obj->minY = obj->minZ = 
			obj->maxX = obj->maxY = obj->maxZ = 
			obj->width = obj->height = obj->depth = 0.0;
		return;
	}
	
	width = obj->childs[0]->width;
	height = obj->childs[0]->height;
	depth = obj->childs[0]->depth;
	
	for (i = 1; obj->childs[i] != NULL; i++) {
		height = (obj->childs[i]->height > height)? 
                                                obj->childs[i]->height: height;
		depth = (obj->childs[i]->depth > depth)? 
                                                obj->childs[i]->depth: depth;
		width += obj->childs[i]->width;
	}
	
	
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
	width = -width/2;
	for (i = 0; i < lay->childs; i++) {
		lay->offsetx[i] = -(obj->childs[i]->maxX + obj->childs[i]->minX)
			                / 2 + width + obj->childs[i]->width/2;
		lay->offsety[i] = -(obj->childs[i]->maxY + obj->childs[i]->minY)
                                                                          / 2;
		lay->offsetz[i] = -(obj->childs[i]->maxZ + obj->childs[i]->minZ)
                                                                          / 2;
		width += obj->childs[i]->width;
	}
}

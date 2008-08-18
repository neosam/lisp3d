#include <stdlib.h>
#include <stdio.h>
#include <SDL_opengl.h>

#include "layouty.h"
#include "elements.h"
#include "parser.h"
#include "graphics.h"

LayoutY *newLayoutY(Object *obj)
{
	LayoutY *lay = (LayoutY*) realloc(obj, sizeof(LayoutY));
	
	return lay;
}

Object *layoutYInit(Object *obj, char **list)
{
	LayoutY *lay;
	obj->type = LAYOUT_Y;
	lay = newLayoutY(obj);
	return (Object *) lay;
}

void layoutYDraw(Object *obj)
{
	int i;
	LayoutY *lay = (LayoutY*) obj;
	
	for (i = 0; obj->childs[i] != NULL; i++) {
		glPushMatrix();
		glTranslatef(lay->offsetx[i], lay->offsety[i], lay->offsetz[i]);
		draw(obj->childs[i]); 
		glPopMatrix();
	}
}

void layoutYSizer(Object *obj)
{
	int i;
	double width, height, depth;
	LayoutY *lay = (LayoutY*) obj;
	
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
		width = (obj->childs[i]->width > width)? 
                                                obj->childs[i]->width: width;
		depth = (obj->childs[i]->depth > depth)? 
                                                obj->childs[i]->depth: depth;
		height += obj->childs[i]->height;
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
	height = -height/2;
	for (i = 0; i < lay->childs; i++) {
		lay->offsety[i] = -(obj->childs[i]->maxY + obj->childs[i]->minY)
                                                       / 2 + height +
			                               obj->childs[i]->height
			                               / 2;
		lay->offsetx[i] = -(obj->childs[i]->maxX + obj->childs[i]->minX)
			                               / 2;
		lay->offsetz[i] = -(obj->childs[i]->maxZ + obj->childs[i]->minZ)
			                               / 2;
		height += obj->childs[i]->height;
	}
}

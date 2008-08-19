/*
 * File layoutx.c
 *
 * lisp3d is the legal property of Simon Goller (neosam@gmail.com).
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

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
		obj->min.x = obj->min.y = obj->min.z = 
			obj->max.x = obj->max.y = obj->max.z = 
			obj->dimension.x = 
		        obj->dimension.y = 
		        obj->dimension.z = 0.0;
		return;
	}
	
	width = obj->childs[0]->dimension.x;
	height = obj->childs[0]->dimension.y;
	depth = obj->childs[0]->dimension.z;
	
	for (i = 1; obj->childs[i] != NULL; i++) {
		height = (obj->childs[i]->dimension.y > height)? 
                                                obj->childs[i]->dimension.y: height;
		depth = (obj->childs[i]->dimension.z > depth)? 
                                                obj->childs[i]->dimension.z: depth;
		width += obj->childs[i]->dimension.x;
	}
	
	
	obj->min.x = -width/2;
	obj->max.x = width/2;
	obj->min.y = -height/2;
	obj->max.y = height/2;
	obj->min.z = -depth/2;
	obj->max.z = depth/2;
	obj->dimension.x = width;
	obj->dimension.y = height;
	obj->dimension.z = depth;
	lay->childs = i;
	
	/* Layouting */
	width = -width/2;
	for (i = 0; i < lay->childs; i++) {
		lay->offsetx[i] = -(obj->childs[i]->max.x + obj->childs[i]->min.x)
			                / 2 + width + obj->childs[i]->dimension.x/2;
		lay->offsety[i] = -(obj->childs[i]->max.y + obj->childs[i]->min.y)
                                                                          / 2;
		lay->offsetz[i] = -(obj->childs[i]->max.z + obj->childs[i]->min.z)
                                                                          / 2;
		width += obj->childs[i]->dimension.x;
	}
}

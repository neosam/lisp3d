/*
 * File layoutz.c
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

#include "layoutz.h"
#include "elements.h"
#include "parser.h"
#include "graphics.h"
#include "misc.h"

LayoutZ *newLayoutZ(Object *obj)
{
	LayoutZ *lay = REALLOC(LayoutZ, obj);
	
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
		glTranslatef(lay->offsetx[i], lay->offsety[i], lay->offsetz[i]);
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
		width = (obj->childs[i]->dimension.x > width)? 
                                                 obj->childs[i]->dimension.x: width;
		depth += obj->childs[i]->dimension.z;
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
	depth = -depth/2;
	for (i = 0; i < lay->childs; i++) {
		lay->offsetz[i] = -(obj->childs[i]->max.z + obj->childs[i]->min.z)
                                            / 2 + depth + obj->childs[i]->dimension.z 
                                            / 2;
		lay->offsety[i] = -(obj->childs[i]->max.y + obj->childs[i]->min.y)
                                            / 2;
		lay->offsetx[i] = -(obj->childs[i]->max.x + obj->childs[i]->min.x)
                                            / 2;
		depth += obj->childs[i]->dimension.z;
	}
}

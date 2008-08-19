/*
 * File rect.c
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
#include <SDL_opengl.h>

#include "rect.h"
#include "parser.h"
#include "elements.h"
#include "misc.h"

Rect *newRect(Object *obj)
{
	Rect *rect = REALLOC(Rect, obj);

	pointValues(&rect->v1, 0, 0, 0);
	pointValues(&rect->v2, 0, 0, 0);
	pointValues(&rect->v3, 0, 0, 0);
	pointValues(&rect->v4, 0, 0, 0);
	pointValues(&rect->color, 0, 0, 0);
	
	return rect;
}

void rectCreateVertices(Rect *rect)
{
	Object *obj = (Object *)rect;
	GLdouble r = rect->color.r,
		g = rect->color.g,
		b = rect->color.b;
	int v1 = objRegisterVertexc(obj, rect->v1.x, rect->v1.y, rect->v1.z, 
				                                   r, g, b),
		v2 = objRegisterVertexc(obj, rect->v2.x, rect->v2.y, 
                                                                   rect->v2.z, 
                                                                   r, g, b),
		v3 = objRegisterVertexc(obj, rect->v3.x, rect->v3.y, 
					                           rect->v3.z, 
                                                                   r, g, b),
		v4 = objRegisterVertexc(obj, rect->v4.x, rect->v4.y, 
					                           rect->v4.z, 
                                                                   r, g, b);
	
	objAddFace(obj, v1, v2, v3);
	objAddFace(obj, v1, v3, v4);
}

Object *rectInit(Object *obj, char **list)
{
	Rect *rect;
	
	obj->type = RECT;
	rect = newRect(obj);
	elemList = list;

	elemSetp("v1", &rect->v1);
	elemSetp("v2", &rect->v2);
	elemSetp("v3", &rect->v3);
	elemSetp("v4", &rect->v4);
	elemSetp("color", &rect->color);
	
	rectCreateVertices(rect);
	
	return (Object *) rect;
}



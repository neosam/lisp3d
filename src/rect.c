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

	rect->x1 = 0.0;
	rect->x2 = 0.0;
	rect->x3 = 0.0;
	rect->x4 = 0.0;
	
	rect->y1 = 0.0;
	rect->y2 = 0.0;
	rect->y3 = 0.0;
	rect->y4 = 0.0;
	
	rect->z1 = 0.0;
	rect->z2 = 0.0;
	rect->z3 = 0.0;
	rect->z4 = 0.0;
	
	rect->r = 0.0;
	rect->g = 0.0;
	rect->b = 0.0;
	
	return rect;
}

void rectCreateVertices(Rect *rect)
{
	Object *obj = (Object *)rect;
	GLdouble r = rect->r,
		g = rect->g,
		b = rect->b;
	int v1 = objRegisterVertexc(obj, rect->x1, rect->y1, rect->z1, r, g, b),
		v2 = objRegisterVertexc(obj, rect->x2, rect->y2, rect->z2, 
                                                                       r, g, b),
		v3 = objRegisterVertexc(obj, rect->x3, rect->y3, rect->z3, 
                                                                       r, g, b),
		v4 = objRegisterVertexc(obj, rect->x4, rect->y4, rect->z4, 
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
	
	elemSetd("x1", &rect->x1);
	elemSetd("x2", &rect->x2);
	elemSetd("x3", &rect->x3);
	elemSetd("x4", &rect->x4);
	
	elemSetd("y1", &rect->y1);
	elemSetd("y2", &rect->y2);
	elemSetd("y3", &rect->y3);
	elemSetd("y4", &rect->y4);
	
	elemSetd("z1", &rect->z1);
	elemSetd("z2", &rect->z2);
	elemSetd("z3", &rect->z3);
	elemSetd("z4", &rect->z4);
	
	elemSetd("r", &rect->r);
	elemSetd("g", &rect->g);
	elemSetd("b", &rect->b);
	
	rectCreateVertices(rect);
	
	return (Object *) rect;
}

void rectDraw(Object *obj)
{
	Rect *rect = (Rect*) obj;
	
	glBegin(GL_QUADS);
	glColor3f(rect->r, rect->g, rect->b);
	glVertex3f(rect->x1, rect->y1, rect->z1);
	glVertex3f(rect->x2, rect->y2, rect->z2);
	glVertex3f(rect->x3, rect->y3, rect->z3);
	glVertex3f(rect->x4, rect->y4, rect->z4);
	glEnd();
}

void rectSizer(Object *obj)
{
	Rect *rect = (Rect*) obj;
	
	double minBuffer = rect->x1, 
		maxBuffer = rect->x1;
	
	if (rect->x2 < minBuffer)
		minBuffer = rect->x2;
	else
		maxBuffer = rect->x2;
	
	minBuffer = (minBuffer < rect->x3)? minBuffer: rect->x3;
	maxBuffer = (maxBuffer > rect->x3)? maxBuffer: rect->x3;
	
	obj->min.x = (minBuffer < rect->x4)? minBuffer: rect->x4;
	obj->max.x = (maxBuffer > rect->x4)? maxBuffer: rect->x4;
	
	minBuffer = rect->y1;
	maxBuffer = rect->y1;
	
	if (rect->y2 < minBuffer)
		minBuffer = rect->y2;
	else
		maxBuffer = rect->y2;
	
	minBuffer = (minBuffer < rect->y3)? minBuffer: rect->y3;
	maxBuffer = (maxBuffer > rect->y3)? maxBuffer: rect->y3;
	
	obj->min.y = (minBuffer < rect->y4)? minBuffer: rect->y4;
	obj->max.y = (maxBuffer > rect->y4)? maxBuffer: rect->y4;
	
	minBuffer = rect->z1;
	maxBuffer = rect->z1;
	
	if (rect->z2 < minBuffer)
		minBuffer = rect->z2;
	else
		maxBuffer = rect->z2;
	
	minBuffer = (minBuffer < rect->z3)? minBuffer: rect->z3;
	maxBuffer = (maxBuffer > rect->z3)? maxBuffer: rect->z3;
	
	obj->min.z = (minBuffer < rect->z4)? minBuffer: rect->z4;
	obj->max.z = (maxBuffer > rect->z4)? maxBuffer: rect->z4;
	
	obj->dimension.x = obj->max.x - obj->min.x;
	obj->dimension.y = obj->max.y - obj->min.y;
	obj->dimension.z = obj->max.z - obj->min.z;
}

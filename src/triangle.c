/*
 * File triangle.c
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

#include "triangle.h"
#include "globalindex.h"
#include "parser.h"
#include "debug.h"
#include "misc.h"

Triangle *newTriangle(Object *obj)
{
	Triangle *tri = REALLOC(Triangle, obj);
	
	tri->x1 = 0.0;
	tri->x2 = 0.0;
	tri->x3 = 0.0;
	tri->y1 = 0.0;
	tri->y2 = 0.0;
	tri->y3 = 0.0;
	tri->z1 = 0.0;
	tri->z2 = 0.0;
	tri->z3 = 0.0;
		
	tri->r = 0.0;
	tri->g = 0.0;
	tri->b = 0.0;

	return tri;
}

void triangleCreateVertices(Triangle *tri)
{
	Object *obj = (Object*) tri;
	GLdouble r = tri->r,
		g = tri->g,
		b = tri->b;
	int p1 = objRegisterVertexc(obj, tri->x1, tri->y1, tri->z1, r, g, b),
		p2 = objRegisterVertexc(obj, tri->x2, tri->y2, tri->z2, 
                                                                    r, g, b),
		p3 = objRegisterVertexc(obj, tri->x3, tri->y3, tri->z3, 
					                            r, g, b);
	
	objAddFace(obj, p1, p2, p3);
	
	assert(obj->ventries == 3);
	assert(obj->fentries == 1);
}

Object *triangleInit(Object *obj, char **list)
{
	obj->type = TRIANGLE;
	Triangle *dst = newTriangle(obj);
	elemList = list;
	
	elemSetd("x1", &dst->x1);
	elemSetd("y1", &dst->y1);
	elemSetd("z1", &dst->z1);
	elemSetd("x2", &dst->x2);
	elemSetd("y2", &dst->y2);
	elemSetd("z2", &dst->z2);
	elemSetd("x3", &dst->x3);
	elemSetd("y3", &dst->y3);
	elemSetd("z3", &dst->z3);
	elemSetd("r", &dst->r);
	elemSetd("g", &dst->g);
	elemSetd("b", &dst->b);
	
	triangleCreateVertices(dst);
	
	return (Object *)dst;
}


double *triangleGetRGB(int index)
{
	double *res = MALLOCN(double, 3);
	Triangle *tri = (Triangle *)getGlobalIndex(index);
	
	res[0] = tri->r;
	res[1] = tri->g;
	res[2] = tri->b;
	
	return res;
}


void triangleSetRGB(int index, double r, double g, double b)
{
	Triangle *tri = (Triangle *)getGlobalIndex(index);
	
	tri->r = r;
	tri->g = g;
	tri->b = b;
}

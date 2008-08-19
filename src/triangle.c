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
	
	pointValues(&tri->v1, 0, 0, 0);
	pointValues(&tri->v2, 0, 0, 0);
	pointValues(&tri->v3, 0, 0, 0);
	pointValues(&tri->color, 0, 0, 0);

	return tri;
}

void triangleCreateVertices(Triangle *tri)
{
	Object *obj = (Object*) tri;
	GLdouble r = tri->color.r,
		g = tri->color.g,
		b = tri->color.b;
	int p1 = objRegisterVertexc(obj, tri->v1.x, tri->v1.y, tri->v1.z, 
                                                                     r, g, b),
		p2 = objRegisterVertexc(obj, tri->v2.x, tri->v2.y, tri->v2.z, 
                                                                    r, g, b),
		p3 = objRegisterVertexc(obj, tri->v3.x, tri->v3.y, tri->v3.z, 
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
	
	elemSetp("v1", &dst->v1);
	elemSetp("v2", &dst->v2);
	elemSetp("v3", &dst->v3);
	elemSetp("color", &dst->color);
	
	triangleCreateVertices(dst);
	
	return (Object *)dst;
}


double *triangleGetRGB(int index)
{
	double *res = MALLOCN(double, 3);
	Triangle *tri = (Triangle *)getGlobalIndex(index);
	
	res[0] = tri->color.r;
	res[1] = tri->color.g;
	res[2] = tri->color.b;
	
	return res;
}


void triangleSetRGB(int index, double r, double g, double b)
{
	Triangle *tri = (Triangle *)getGlobalIndex(index);
	
	tri->color.r = r;
	tri->color.g = g;
	tri->color.b = b;
}

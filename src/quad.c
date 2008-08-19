/*
 * File quad.c
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

#include "quad.h"
#include "globalindex.h"
#include "parser.h"
#include "debug.h"
#include "misc.h"

Quad *newQuad(Object *obj)
{
	Quad *quad = REALLOC(Quad, obj);
	
	quad->size.x = 0.0;
	quad->size.y = 0.0;
	quad->size.z = 0.0;

	return quad;
}

void quadCreateVertices(Quad *quad)
{
	Object *obj = (Object *)quad;
	double sizeX = quad->size.x,
		sizeY = quad->size.y,
		sizeZ = quad->size.z,
		r = quad->color.r, g = quad->color.g, b = quad->color.b;
	
	int 
		ftopleft = objRegisterVertexc(obj, -sizeX/2,  sizeY/2,  sizeZ/2,
					      r, g, b), 
		btopleft = objRegisterVertexc(obj, -sizeX/2,  sizeY/2, -sizeZ/2,
					      r, g, b),
		ftopright = objRegisterVertexc(obj,  
					       sizeX/2,  sizeY/2,  sizeZ/2,
					       r, g, b), 
		btopright = objRegisterVertexc(obj,  
					       sizeX/2,  sizeY/2, -sizeZ/2,
					       r, g, b),
		fbottomleft = objRegisterVertexc(obj, 
						 -sizeX/2, -sizeY/2,  sizeZ/2,
						 r, g, b),
		bbottomleft = objRegisterVertexc(obj, 
						 -sizeX/2, -sizeY/2, -sizeZ/2,
						 r, g, b),
		fbottomright = objRegisterVertexc(obj,  
						  sizeX/2, -sizeY/2,  sizeZ/2,
						  r, g, b), 
		bbottomright = objRegisterVertexc(obj,  
						  sizeX/2, -sizeY/2, -sizeZ/2,
						  r, g, b);
	
#ifndef NDEBUG
	printf("DEBUG: %i %i %i %i %i %i %i %i\n",
	       ftopleft, btopleft,
	       ftopright, btopright,
	       fbottomleft, bbottomleft,
	       fbottomright, bbottomright);
#endif
	
	/* Front */
	objAddFace(obj, ftopright, ftopleft, fbottomleft);
	objAddFace(obj, ftopright, fbottomleft, fbottomright);
	
	/* Back */
	objAddFace(obj, btopright, bbottomleft, btopleft);
	objAddFace(obj, btopright, bbottomright, bbottomleft);
	
	/* Left */
	objAddFace(obj, ftopleft, btopleft, bbottomleft);
	objAddFace(obj, ftopleft, bbottomleft, fbottomleft);
	
	/* Right */
	objAddFace(obj, ftopright, bbottomright, btopright);
	objAddFace(obj, ftopright, fbottomright, bbottomright);
	
	/* Up */
	objAddFace(obj, ftopright, btopleft, ftopleft);
	objAddFace(obj, ftopright, btopright, btopleft);
	
	/* Down */
	objAddFace(obj, fbottomright, fbottomleft, bbottomleft);
	objAddFace(obj, fbottomright, bbottomleft, bbottomright);
}

Object *quadInit(Object *obj, char **list)
{
	Quad *quad;
	
	obj->type = QUAD;
	quad = newQuad(obj);
	elemList = list;
	
	elemSetp("size", &quad->size);
	elemSetp("color", &quad->color);
	
	quadCreateVertices(quad);
	
	return (Object*) quad;
}



double *quadGetRGB(int index)
{
	double *res = MALLOCN(double, 3);
	Quad *quad = (Quad *)getGlobalIndex(index);
	
	res[0] = quad->color.r;
	res[1] = quad->color.g;
	res[2] = quad->color.b;
	
	return res;
}


void quadSetRGB(int index, double r, double g, double b)
{
	Quad *quad = (Quad *)getGlobalIndex(index);
	Object *obj = (Object *)quad;
	GLdouble *color;
	int i;
	
	quad->color.r = r;
	quad->color.g = g;
	quad->color.b = b;
	
	for (i = 0; i < obj->ventries; i++) {
		color = C(obj, i);
		color[0] = r;
		color[1] = g;
		color[2] = b;
	}
}

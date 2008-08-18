/*
 * File triangle.h
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

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "object.h"

/* Quad object */
struct Triangle {
	Object obj;
	
	/* vertex */
	double x1, y1, z1;
	double x2, y2, z2;
	double x3, y3, z3;
	double r, g, b;
};
typedef struct Triangle Triangle;

Triangle *newTriangle(Object *obj);
Object *triangleInit(Object *obj, char **list);
void triangleDraw(Object *obj);
void triangleSizer(Object *obj);

/* Commands for global index */
double *triangleGetRGB(int index);
void triangleSetRGB(int index, double r, double g, double b);


#endif

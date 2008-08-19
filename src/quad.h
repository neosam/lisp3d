/*
 * File quad.h
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

#ifndef QUAD_H
#define QUAD_H

#include "object.h"
#include "types.h"

/* Quad object */
struct Quad {
	Object obj;
	
	/* Dimensions */
	union {
		Point size;
		struct {
			double sizeX, sizeY, sizeZ;
		};
	};
	union {
		Point color;
		struct {
			double r, g, b;
		};
	};
};
typedef struct Quad Quad;

Quad *newQuad(Object *obj);
Object *quadInit(Object *obj, char **list);
void quadSizer(Object *obj);

/* Commands for global index */
double *quadGetRGB(int index);
void quadSetRGB(int index, double r, double g, double b);


#endif

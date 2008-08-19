/*
 * File types.h
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


#ifndef L3D_TYPES_H
#define L3D_TYPES_H

#include <SDL_opengl.h>

struct Point
{
	union {
		GLdouble x, r;
	};
	union {
		GLdouble y, g;
	};
	union {
		GLdouble z, b;
	};
};
typedef struct Point Point;

#define POINT_ARRAY(p) ((GLdouble*)&p)

void pointValues(Point *p, GLdouble x, GLdouble y, GLdouble z);

#endif

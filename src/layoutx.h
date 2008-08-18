/*
 * File layoutx.h
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

#ifndef LAYOUTX_H
#define LAYOUTX_H

#include "object.h"

struct LayoutX {
	Object obj;
	double offsetx[255];
	double offsety[255];
	double offsetz[255];
	int childs;
};
typedef struct LayoutX LayoutX;

LayoutX *newLayoutX(Object *obj);
Object *layoutXInit(Object *obj, char **list);
void layoutXDraw(Object *obj);
void layoutXSizer(Object *obj);

#endif

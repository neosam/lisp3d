/*
 * File elements.h
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

#ifndef ELEMENTS_H
#define ELEMENTS_H

#include "object.h"
#include "quad.h"
#include "camera.h"
#include "triangle.h"
#include "rect.h"
#include "layoutinner.h"
#include "layoutx.h"
#include "layouty.h"
#include "layoutz.h"
#include "usertag.h"

#define CQUAD(x) ((Quad*)(x))

struct _tags {
	char *name;
	Object *(*initfunc)(Object *obj, char **list);
	void (*drawfunc)(Object *obj);
	void (*sizerfunc)(Object *obj);
	Object *ref;
};

extern struct _tags *taglist;


/* Build in types */
enum ObjType {
	OBJECT = 0,
	QUAD,
	TRIANGLE,
	RECT,
	LAYOUT_INNER,
	LAYOUT_X,
	LAYOUT_Y,
	LAYOUT_Z,
	CAMERA,
	CODE,
	LASTELEM
};

void registerTag(char *name, Object*(*initfunc)(Object *obj, char **list),
		 void (*drawfunc)(Object *obj), 
		 void (*sizerfunc)(Object *obj), Object *ref);

void initElements();

#endif

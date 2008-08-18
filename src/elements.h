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

/*
 * This file handles the whole elements which exist in lisp3d
 */

#ifndef ELEMENTS_H
#define ELEMENTS_H

/*
 * Load all elements
 */
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


/*
 * The taglist is an array that connects an element with functions.
 *
 * There are three functions now:
 *         - initfunc,
 *         - drawfunc and
 *         - sizerfuc
 *
 * initfunc is called by the parser after the element type is detected.
 * That function should allocate memory and should set the values.
 * If you set the vertex and face data in this function there will be no
 * need to create a display and sizer function.
 *
 * drawfunc is called if the element should be drawn.  If you used vertex
 * and face data in initfunc you can pass objDraw
 * 
 * sizerfunc set the objectattributes min*, max*, width, height and depth.
 * These attributes are needed by the layouter.
 */
struct _tags {
	char *name;
	Object *(*initfunc)(Object *obj, char **list);
	void (*drawfunc)(Object *obj);
	void (*sizerfunc)(Object *obj);
	Object *ref;
};

extern struct _tags *taglist;



/* 
 * Element types
 *
 * Here the element types are defined.  Important is that OBJECT is zero
 * and CAMERA is the first non-drawable element.
 */
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

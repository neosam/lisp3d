/*
 * File layoutinner.c
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

#include "layoutinner.h"
#include "elements.h"
#include "parser.h"
#include "graphics.h"
#include "debug.h"
#include "misc.h"

LayoutInner *newLayoutInner(Object *obj)
{
	LayoutInner *lay = REALLOC(LayoutInner, obj);
	
	return lay;
}

Object *layoutInnerInit(Object *obj, char **list)
{
	LayoutInner *lay;
	obj->type = LAYOUT_INNER;
	lay = newLayoutInner(obj);
	return (Object *) lay;
}

void layoutInnerDraw(Object *obj)
{
	int i;
	
	assert(obj!=NULL);
	assert(obj->childs != NULL);
	for (i = 0; obj->childs[i] != NULL; i++) {
		draw(obj->childs[i]); 
  }
}

void layoutInnerSizer(Object *obj)
{
	int i;
	double minx, maxx,
		miny, maxy,
		minz, maxz;
	
	if (obj->childs[0] == NULL) {
		obj->minX = obj->minY = obj->minZ = 
			obj->maxX = obj->maxY = obj->maxZ = 
			obj->width = obj->height = obj->depth = 0.0;
		return;
	}
	
	minx = obj->childs[0]->minX;
	maxx = obj->childs[0]->maxX;
	
	miny = obj->childs[0]->minY;
	maxy = obj->childs[0]->maxY;
	
	minz = obj->childs[0]->minZ;
	maxz = obj->childs[0]->maxZ;
	
	for (i = 1; obj->childs[i] != NULL; i++) {
		minx = (obj->childs[i]->minX < minx)? obj->childs[i]->minX: 
			                                                 minx;
		maxx = (obj->childs[i]->maxX > maxx)? obj->childs[i]->maxX: 
                                                                         maxx;
		miny = (obj->childs[i]->minY < miny)? obj->childs[i]->minY: 
                                                                         miny;
		maxy = (obj->childs[i]->maxY > maxy)? obj->childs[i]->maxY: 
                                                                         maxy;
		minz = (obj->childs[i]->minZ < minz)? obj->childs[i]->minZ: 
                                                                         minz;
		maxz = (obj->childs[i]->maxZ > maxz)? obj->childs[i]->maxZ: 
                                                                         maxz;
	}
	
	obj->minX = minx;
	obj->maxX = maxx;
	obj->minY = miny;
	obj->maxY = maxy;
	obj->minZ = minz;
	obj->maxZ = maxz;
	obj->width = maxx - minx;
	obj->height = maxy - miny;
	obj->depth = maxz - minz;
}

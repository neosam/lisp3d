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
		obj->min.x = obj->min.y = obj->min.z = 
			obj->max.x = obj->max.y = obj->max.z = 
			obj->dimension.x = 
                        obj->dimension.y = 
                        obj->dimension.z = 0.0;
		return;
	}
	
	minx = obj->childs[0]->min.x;
	maxx = obj->childs[0]->max.x;
	
	miny = obj->childs[0]->min.y;
	maxy = obj->childs[0]->max.y;
	
	minz = obj->childs[0]->min.z;
	maxz = obj->childs[0]->max.z;
	
	for (i = 1; obj->childs[i] != NULL; i++) {
		minx = (obj->childs[i]->min.x < minx)? obj->childs[i]->min.x: 
			                                                 minx;
		maxx = (obj->childs[i]->max.x > maxx)? obj->childs[i]->max.x: 
                                                                         maxx;
		miny = (obj->childs[i]->min.y < miny)? obj->childs[i]->min.y: 
                                                                         miny;
		maxy = (obj->childs[i]->max.y > maxy)? obj->childs[i]->max.y: 
                                                                         maxy;
		minz = (obj->childs[i]->min.z < minz)? obj->childs[i]->min.z: 
                                                                         minz;
		maxz = (obj->childs[i]->max.z > maxz)? obj->childs[i]->max.z: 
                                                                         maxz;
	}
	
	obj->min.x = minx;
	obj->max.x = maxx;
	obj->min.y = miny;
	obj->max.y = maxy;
	obj->min.z = minz;
	obj->max.z = maxz;
	obj->dimension.x = maxx - minx;
	obj->dimension.y = maxy - miny;
	obj->dimension.z = maxz - minz;
}

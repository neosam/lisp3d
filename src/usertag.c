/*
 * File usertag.c
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
#include <string.h>

#include "usertag.h"
#include "debug.h"
#include "elements.h"
#include "parser.h"
#include "graphics.h"
#include "misc.h"


Usertag *newUsertag(Object *obj)
{
	Usertag *utag = MALLOC(Usertag);
	
	DMSG("Create new Usertag\n");
	utag->obj = *obj;
	
	return utag;
}


Object *usertagInit(Object *obj, char **list) 
{
	Usertag *utag;
	char *tagname = lookupList(list, "tagname");
	int i;
	
	for (i = 0; taglist[i].name != NULL; i++) {
		if (strcmp(tagname, taglist[i].name) == 0) {
			obj->type = i;
			break;
		}
	}
	utag = newUsertag(obj);
	assert(strcmp(tagname, taglist[obj->type].name) == 0);
	
	return (Object *)utag;
}


void usertagDraw(Object *obj)
{
	Usertag *utag = (Usertag*) obj;
	
	assert(taglist[obj->type].ref != NULL);
	draw(taglist[obj->type].ref);

}

void usertagSizer(Object *obj)
{
	Object *ref = taglist[obj->type].ref;
	
	obj->minX = ref->minX;
	obj->maxX = ref->maxX;
	obj->minY = ref->minY;
	obj->maxY = ref->maxY;
	obj->minZ = ref->minZ;
	obj->maxZ = ref->maxZ;
	obj->width = ref->width;
	obj->height = ref->height;
	obj->depth = ref->depth;
}

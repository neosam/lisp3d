/*
 * File object.c
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


#include <stdio.h>
#include <stdlib.h>

#include "object.h"
#include "globalindex.h"
#include "parser.h"
#include "elements.h"
#include "debug.h"
#include "misc.h"

Object *newObject()
{
	Object *object = MALLOC(Object);
	
	object->type = 0;
	
	object->name = NULL;
	object->nameID = 0;
	
	object->class = NULL;
	object->classID = 0;
	
	object->onInit = NULL;
	object->onDraw = NULL;
	
	object->dimension.x = 0.0;
	object->dimension.y = 0.0;
	object->dimension.z = 0.0;
	
	object->min.x = 0.0;
	object->max.x = 0.0;
	object->min.y = 0.0;
	object->max.y = 0.0;
	object->min.z = 0.0;
	object->max.z = 0.0;
	object->sized = 0;
	
	
	/* Initialize vertex attributes */
	object->vertices = MALLOCN(GLdouble, OBJ_ENTRY*3);
	object->colors = MALLOCN(GLdouble, OBJ_ENTRY*3);
	object->normals = MALLOCN(GLdouble, OBJ_ENTRY*3);
	object->faces = MALLOCN(GLint, OBJ_ENTRY*3);
	object->ventries = object->fentries = 0;
	object->vsize = object->fsize = OBJ_ENTRY;

	return object;
}

Object *objectInit(char **list)
{
	Object *object = newObject();
	
	elemList = list;
	
	elemSets("name", &object->name);
	elemSets("class", &object->class);
	elemSets("onDraw", &object->onDraw);
	elemSets("onInit", &object->onInit);
	
	elemSetp("dimension", &object->dimension);
	elemSetp("min", &object->min);
	elemSetp("max", &object->max);
	
	printf("Tagname: %s\n", lookupList(list, "tagname"));
	
	/* User defined objects */
	if (object->name != NULL) {
#ifndef NDEBUG
		printf("DEBUG: Create Usertag %s\n", object->name);
#endif
		registerTag(object->name,
			    usertagInit, usertagDraw, usertagSizer, object);
		DMSG("User Tag created\n");
	}
	
	
	return object;
}


char *objGetName(int index)
{
	return getGlobalIndex(index)->name;
}


void objCheckArrays(Object *obj)
{
	/* TODO */
}

void objDoSizer(Object *obj, GLdouble x, GLdouble y, GLdouble z)
{
	switch (obj->sized) {
	case 0:
		obj->min.x = obj->max.x = x;
		obj->min.y = obj->max.y = y;
		obj->min.z = obj->max.z = z;
		obj->sized = 1;
		break;
	case 1:
		if (x < obj->min.x)
			obj->min.x = x;
		if (x > obj->max.x)
			obj->max.x = x;
    
		if (y < obj->min.y)
			obj->min.y = y;
		if (y > obj->max.y)
			obj->max.y = y;
		
		if (z < obj->min.z)
			obj->min.z = z;
		if (z > obj->max.z)
			obj->max.z = z;
		break;
	}
	
	obj->dimension.x = obj->max.x - obj->min.x;
	obj->dimension.y = obj->max.y - obj->min.y;
	obj->dimension.z = obj->max.z - obj->min.z;
	

	assert(obj->dimension.x >= 0.0);
	assert(obj->dimension.y >= 0.0);
	assert(obj->dimension.z >= 0.0);
	assert(obj->min.x <= x);
	assert(obj->max.x >= x);
	assert(obj->min.y <= y);
	assert(obj->max.y >= y);
	assert(obj->min.z <= z);
	assert(obj->max.z >= z);
}

GLint objRegisterVertex(Object *obj,
			GLdouble x,
			GLdouble y,
			GLdouble z)
{
	GLdouble *vertex = V(obj, obj->ventries), 
		*color = C(obj, obj->ventries);
	
	vertex[0] = x;
	vertex[1] = y;
	vertex[2] = z;

	color[0] = 0.0;
	color[1] = 0.0;
	color[2] = 0.0;
	
	obj->ventries++;
	
	objDoSizer(obj, x, y, z);
	
	objCheckArrays(obj);

	return obj->ventries-1;
}

GLint objRegisterVertexc(Object *obj,
			 GLdouble x,
			 GLdouble y,
			 GLdouble z,
			 GLdouble r,
			 GLdouble g,
			 GLdouble b)
{
	GLdouble *vertex = V(obj, obj->ventries), 
		*color = C(obj, obj->ventries);
	
	vertex[0] = x;
	vertex[1] = y;
	vertex[2] = z;
	
	color[0] = r;
	color[1] = g;
	color[2] = b;
	
	obj->ventries++;
	
	objDoSizer(obj, x, y, z);
	
	objCheckArrays(obj);
	
	return obj->ventries-1;
}


int objAddFace(Object *obj, GLint v1, GLint v2, GLint v3)
{
	GLint *face = F(obj, obj->fentries);
	GLdouble tmp1[3], tmp2[3];
	
	face[0] = v1;
	face[1] = v2;
	face[2] = v3;
	
	/* Calculate face normal */
	vertexXvertex3(N(obj, obj->fentries),
		       subVertex3(tmp1, V(obj, v1), V(obj, v2)),
		       subVertex3(tmp2, V(obj, v2), V(obj, v3)));
	
	
	obj->fentries++;
	
	objCheckArrays(obj);
	
#ifndef NDEBUG
	printf("DEBUG Added face: %i\n", obj->fentries-1);
#endif
	
	return obj->fentries-1;
}

void objDraw(Object *obj)
{
	int i;
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	
	glVertexPointer(3, GL_DOUBLE, 0, obj->vertices);
	glColorPointer(3, GL_DOUBLE, 0, obj->colors);
	
	for (i = 0; i < obj->fentries; i++) {
		glNormal3dv(N(obj, i));
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, F(obj, i));
	}
}

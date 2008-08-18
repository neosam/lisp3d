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
	
	object->width = 0.0;
	object->height = 0.0;
	object->depth = 0.0;
	
	object->minX = 0.0;
	object->maxX = 0.0;
	object->minY = 0.0;
	object->maxY = 0.0;
	object->minZ = 0.0;
	object->maxZ = 0.0;
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
	
	elemSetd("minX", &object->minX);
	elemSetd("maxX", &object->maxX);
	elemSetd("minY", &object->minY);
	elemSetd("maxY", &object->maxY);
	elemSetd("minZ", &object->minZ);
	elemSetd("maxZ", &object->maxZ);
	elemSetd("width", &object->width);
	elemSetd("height", &object->height);
	elemSetd("depth", &object->depth);
	
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
		obj->minX = obj->maxX = x;
		obj->minY = obj->maxY = y;
		obj->minZ = obj->maxZ = z;
		obj->sized = 1;
		break;
	case 1:
		if (x < obj->minX)
			obj->minX = x;
		if (x > obj->maxX)
			obj->maxX = x;
    
		if (y < obj->minY)
			obj->minY = y;
		if (y > obj->maxY)
			obj->maxY = y;
		
		if (z < obj->minZ)
			obj->minZ = z;
		if (z > obj->maxZ)
			obj->maxZ = z;
		break;
	}
	
	obj->width = obj->maxX - obj->minX;
	obj->height = obj->maxY - obj->minY;
	obj->depth = obj->maxZ - obj->minZ;
	

	assert(obj->width >= 0.0);
	assert(obj->height >= 0.0);
	assert(obj->depth >= 0.0);
	assert(obj->minX <= x);
	assert(obj->maxX >= x);
	assert(obj->minY <= y);
	assert(obj->maxY >= y);
	assert(obj->minZ <= z);
	assert(obj->maxZ >= z);
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

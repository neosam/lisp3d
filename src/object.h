/*
 * File object.h
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
 * Handler for object
 *
 * An object is the base of every element in lisp3d.  It contains important
 * attributes eg the type, pointer to parent and childs, sizers, events
 * and vertices.  Every element has to set object as the first attribute
 * (no pointer):
 *
 *         struct MyElement{
 *                 Object obj;
 *                 ...
 *         };
 *         typedef MyElement MyElement;
 *
 * So access object attributes is very simple:
 *
 *         ((Object*)aElement)->parent = NULL;
 *
 * You also can expand an object to a element:
 *
 *         MyElement *elem = REALLOC(MyElement, obj);
 *
 */

#ifndef OBJECT_H
#define OBJECT_H

#include <SDL_opengl.h>
#include "types.h"
#define OBJ_ENTRY 256

/* Standard object */
struct Object {
	/* Type of object */
	int type;
	int id;
	struct Object *parent;
	struct Object **childs;
	
	/* Name */
	char *name;
	int nameID;
	
	/* Class */
	char *class;
	int classID;
	
	/* Events */
	char *onDraw, *onInit;
	
	/* Sizer variables */
	Point dimension;
	Point min;
	Point max;
	int sized;
	
	/* Mesh settings */
	GLdouble *vertices;              /* Vertices of the mesh */
	GLdouble *colors;                /* Vertex color */
	GLdouble *normals;               /* Face normals */
	GLint *faces;                    /* Triangles hold three meshes */
	int ventries, fentries,          /* Count entries */
		vsize, fsize;            /* Size of the arrays */
	
}; 
typedef struct Object Object;

/* 
 * Macros for vertex access
 */
#define V(obj, i) (obj->vertices + i*3)
#define C(obj, i) (obj->colors + i*3)
#define N(obj, i) (obj->normals + i*3)
#define F(obj, i) (obj->faces + i*3)


Object *newObject();
Object *objectInit(char **list);

char *objGetName(int index);

/* 
 * Object mesh manipulation functions
 * 
 * objCheckArrays reallocs memory if neccessery.
 *
 * objRegisterVertex and objRegisterVertexc adds a vertex to the vertex list 
 * of the array.
 *
 * objAddFace adds a face to the vertex and calculates an face normal.
 */
void objCheckArrays(Object *obj);
GLint objRegisterVertex(Object *obj,
			GLdouble x,
			GLdouble y,
			GLdouble z);
GLint objRegisterVertexc(Object *obj,
			 GLdouble x,
			 GLdouble y,
			 GLdouble z,
			 GLdouble r,
			 GLdouble g,
			 GLdouble b);
int objAddFace(Object *obj, GLint v1, GLint v2, GLint v3);
void objDraw(Object *obj);

#endif

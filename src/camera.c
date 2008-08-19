/*
 * File camera.c
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
#include <SDL_opengl.h>

#include "camera.h"
#include "globalindex.h"
#include "parser.h"
#include "misc.h"

Camera *cam = NULL;

Camera *newCamera(Object *obj)
{
	Camera *result = REALLOC(Camera, obj);

	pointValues(&result->pos, 0, 0, 0);
	pointValues(&result->lookat, 0, 0, 0);
	pointValues(&result->up, 0, 0, 0);
	
	result->fovy = 60.0;
	result->aspect = 1.33333;
}

Object *cameraInit(Object *obj, char **list)
{
	obj->type = CAMERA;
	Camera *dst = newCamera(obj);
	char *buffer;
	elemList = list;
	
	elemSetp("pos", &dst->pos);
	elemSetp("lookat", &dst->lookat);	
	elemSetp("up", &dst->up);	
	
	elemSetd("fovy", &dst->fovy);
	elemSetd("aspect", &dst->aspect);
	

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(dst->fovy, dst->aspect, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
	
	cam = dst;
	
	return (Object*)dst;
}

void cameraDraw(Object *obj)
{
	
}

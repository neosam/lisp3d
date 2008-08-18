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
	
	result->x = 0.0;
	result->y = 0.0;
	result->z = 0.0;
	
	result->frontX = 0.0;
	result->frontY = 0.0;
	result->frontZ = -1.0;
	
	result->upX = 0.0;
	result->upY = 1.0;
	result->upZ = 0.0;
	
	result->fovy = 60.0;
	result->aspect = 1.33333;
}

Object *cameraInit(Object *obj, char **list)
{
	obj->type = CAMERA;
	Camera *dst = newCamera(obj);
	char *buffer;
	elemList = list;
	
	elemSetd("x", &dst->x);
	elemSetd("y", &dst->y);
	elemSetd("z", &dst->z);
	
	elemSetd("frontX", &dst->frontX);
	elemSetd("frontY", &dst->frontY);
	elemSetd("frontZ", &dst->frontZ);
	
	elemSetd("upX", &dst->upX);
	elemSetd("upY", &dst->upY);
	elemSetd("upZ", &dst->upZ);
	
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

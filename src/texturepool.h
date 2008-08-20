#ifndef TEXTUREPOOL_H
#define TEXTUREPOOL_H

#include <SDL_opengl.h>

struct TexturepoolElem
{
	char *filename;
	GLint index;
};
typedef struct TexturepoolElem TexturepoolElem;

extern TexturepoolElem *texturepool;

void texturepoolInit();
GLint texturepoolGet(char *filename);

#endif

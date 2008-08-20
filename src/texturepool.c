/*
 * File texturepool.c
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

#include <SDL_image.h>
#include <string.h>
#include "texturepool.h"
#include "misc.h"

TexturepoolElem *texturepool;
GLint size;
GLint entries;

void texturepoolInit()
{
	size = 256;
	entries = 0;
	texturepool = MALLOCN(TexturepoolElem, size);
	texturepool->filename = NULL;
}

/* 
 * Search in texturepool for the given filename.
 * Return the integer opengl represents as this texture or -1 if the file
 * is not loaded.
 */
GLint texturepoolSearch(char *filename)
{
	TexturepoolElem *telem;
	
	for (telem = texturepool; telem->filename != NULL; telem++)
		if (strcmp(telem->filename, filename) == 0)
			return telem->index;
	return -1;
}

/*
 * Loads the given filename and register it in OpenGL.  Returns the
 * representatio of OpenGL or -2 if loading failed.
 */
GLint texturepoolLoadImage(char *filename)
{
	SDL_Surface *img = IMG_Load(filename);
	GLuint index;
	if (img == NULL)
		return -2;

	/* TODO: Convert pixel data */
	
	glGenTextures(1, &index);
	glBindTexture(GL_TEXTURE_2D, index);
	switch (glGetError()) {
	case GL_INVALID_ENUM:
		printf("Invalid enum\n");
		break;
	case GL_INVALID_OPERATION:
		printf("Invalid operation\n");
		break;
	} 	
	
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, img->w, img->h, GL_RGBA,
			  GL_UNSIGNED_BYTE, img->pixels);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
			GL_LINEAR_MIPMAP_LINEAR); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return index;
}

/*
 * Insert a texture file into the texturepool.
 * Return the representation of OpenGL.
 */
GLint texturepoolInsert(char *filename)
{
	GLint index = texturepoolLoadImage(filename);
	texturepool[entries].filename = filename;
	texturepool[entries].index = index;
	entries++;
	texturepool[entries].filename = NULL;
	return index;
}

/* 
 * Looks this texture is alreade loaded.  If not it will load and insert
 * it automatically. 
 * Returns an integer which OpenGL represents as the texture
 */
GLint texturepoolGet(char *filename)
{
	GLint tex = texturepoolSearch(filename);
	return (tex < 0)? texturepoolInsert(filename): tex;
}

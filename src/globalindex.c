/*
 * File globalindex.c
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
#include "globalindex.h"
#include "debug.h"
#include "misc.h"

#define MINSIZE 256
#define RESIZE 256

int size;
int pos;

Object **globalIndex;

void initGlobalIndex()
{
	DMSG("GlobalIndex init\n");
	globalIndex = MALLOCN(Object*, MINSIZE);
	size = MINSIZE;
	pos = 0;
	DMSG("GlobalIndex init done\n");
}

void insertGlobalIndex(Object *obj)
{
	DMSG("GlobalIndex insert\n");
	if (pos == size-1) {
		size += RESIZE;
		globalIndex = REALLOCN(Object*, globalIndex, size);
	}
	
	globalIndex[pos] = obj;
	obj->id = pos;
	
	pos++;
	DMSG("GlobalIndex insert done\n");
}

Object *getGlobalIndex(int index)
{
	return globalIndex[index];
}

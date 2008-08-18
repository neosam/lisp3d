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

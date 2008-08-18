#include <stdlib.h>

#include "graphics.h"
#include "elements.h"
#include "debug.h"

void draw(Object *obj) {
	int i;
	
	assert (obj!=NULL);
	if (obj->onDraw != NULL)
		execEvent(obj->onDraw, obj);
	
	if (obj->type > 0 && obj->type < CAMERA || obj->type >= LASTELEM) {
		assert (taglist[obj->type].drawfunc);
		taglist[obj->type].drawfunc(obj);
	}
}

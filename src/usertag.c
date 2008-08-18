#include <stdlib.h>
#include <string.h>

#include "usertag.h"
#include "debug.h"
#include "elements.h"
#include "parser.h"
#include "graphics.h"


Usertag *newUsertag(Object *obj)
{
	Usertag *utag = (Usertag*) malloc(sizeof(Usertag));
	
	DMSG("Create new Usertag\n");
	utag->obj = *obj;
	
	return utag;
}


Object *usertagInit(Object *obj, char **list) 
{
	Usertag *utag;
	char *tagname = lookupList(list, "tagname");
	int i;
	
	for (i = 0; taglist[i].name != NULL; i++) {
		if (strcmp(tagname, taglist[i].name) == 0) {
			obj->type = i;
			break;
		}
	}
	utag = newUsertag(obj);
	assert(strcmp(tagname, taglist[obj->type].name) == 0);
	
	return (Object *)utag;
}


void usertagDraw(Object *obj)
{
	Usertag *utag = (Usertag*) obj;
	
	assert(taglist[obj->type].ref != NULL);
	draw(taglist[obj->type].ref);

}

void usertagSizer(Object *obj)
{
	Object *ref = taglist[obj->type].ref;
	
	obj->minX = ref->minX;
	obj->maxX = ref->maxX;
	obj->minY = ref->minY;
	obj->maxY = ref->maxY;
	obj->minZ = ref->minZ;
	obj->maxZ = ref->maxZ;
	obj->width = ref->width;
	obj->height = ref->height;
	obj->depth = ref->depth;
}

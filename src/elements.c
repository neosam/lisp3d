#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "elements.h"
#include "globalindex.h"
#include "debug.h"
#include "misc.h"


/*
 * Taglist must be in the same order as enum 
 * ObjType in elements.h
 * If not, the wrong object will be drawn ;)  
 */

/* 
 * order: {tagname(char*), init-function, draw-function}
 * initfunction is from type: Object *initFunc(Object *obj, char **list)
 * drawfunction is from type: void drawFunc(Object *obj) 
 */

struct _tags *taglist;

int count = 0;
int max = 256;

void registerTag(char *name, Object*(*initfunc)(Object *obj, char **list),
		 void (*drawfunc)(Object *obj), 
		 void (*sizerfunc)(Object *obj), Object *ref)
{
	taglist[count].name = name;
	taglist[count].initfunc = initfunc;
	taglist[count].drawfunc = drawfunc;
	taglist[count].sizerfunc = sizerfunc;
	taglist[count].ref = ref;
	count++;
	if (count == max) {
		max += 256;
		taglist = REALLOCN(struct _tags, taglist, max);
	} 
	taglist[count].name = NULL;
	taglist[count].initfunc = NULL;
	taglist[count].drawfunc = NULL;
	taglist[count].sizerfunc = NULL;
	taglist[count].ref = NULL;
	assert(strcmp(taglist[count-1].name, name) == 0);
}

void initElements()
{    
	DMSG("Starting init elements\n");
	taglist = MALLOCN(struct _tags, max);
	registerTag("object", NULL, NULL, NULL, NULL);
	registerTag("quad", quadInit, objDraw, NULL, NULL);
	registerTag("triangle", triangleInit, objDraw, NULL, NULL);
	registerTag("rect", rectInit, objDraw, NULL, NULL);
	registerTag("layout-inner", layoutInnerInit, layoutInnerDraw, layoutInnerSizer, NULL);
	registerTag("layout-x", layoutXInit, layoutXDraw, layoutXSizer, NULL);
	registerTag("layout-y", layoutYInit, layoutYDraw, layoutYSizer, NULL);
	registerTag("layout-z", layoutZInit, layoutZDraw, layoutZSizer, NULL);
	registerTag("camera", cameraInit, cameraDraw, NULL, NULL);
	registerTag("code", NULL, NULL, NULL, NULL);
	assert(strcmp(taglist[OBJECT].name, "object") == 0);
	assert(strcmp(taglist[QUAD].name, "quad") == 0);
	assert(strcmp(taglist[LAYOUT_X].name, "layout-x") == 0);
	/* registerTag(NULL, NULL, NULL, NULL); /* Last must be null */
}

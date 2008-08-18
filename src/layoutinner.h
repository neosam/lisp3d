#ifndef LAYOUTINNER_H
#define LAYOUTINNER_H

#include "object.h"

struct LayoutInner {
	Object obj;
};
typedef struct LayoutInner LayoutInner;

LayoutInner *newLayoutInner(Object *obj);
Object *layoutInnerInit(Object *obj, char **list);
void layoutInnerDraw(Object *obj);
void layoutInnerSizer(Object *obj);

#endif

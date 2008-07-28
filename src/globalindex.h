#ifndef GLOBALINDEX_H
#define GLOBALINDEX_H

#include "elements.h"

extern Object **globalIndex;

void initGlobalIndex();
void insertGlobalIndex(Object *obj);
Object *getGlobalIndex(int index);



#endif

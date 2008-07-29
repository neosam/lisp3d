#ifndef USERTAG_H
#define USERTAG_H

#include "object.h"

struct Usertag {
  Object obj;

  Object *link;
};
typedef struct Usertag Usertag;

Usertag *newUsertag(Object *obj);
Object *usertagInit(Object *obj, char **list);
void usertagDraw(Object *obj);
void usertagSizer(Object *obj);

#endif


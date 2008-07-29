#ifndef OBJECT_H
#define OBJECT_H

/* Standard object */
struct Object {
  /* Type of object */
  int type;
  int id;
  struct Object *parent;
  struct Object **childs;
  
  /* Name */
  char *name;
  int nameID;

  /* Class */
  char *class;
  int classID;

  /* Events */
  char *onDraw, *onInit;

  /* Draw variables */
  double width, height, depth;
  double minX, minY, minZ;
  double maxX, maxY, maxZ;
}; 
typedef struct Object Object;

Object *newObject();
Object *objectInit(char **list);

char *objGetName(int index);


#endif

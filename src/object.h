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
}; 
typedef struct Object Object;

Object *newObject(int type, Object *parent, char *name, char *class);

char *objGetName(int index);


#endif

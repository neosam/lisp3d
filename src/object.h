#ifndef OBJECT_H
#define OBJECT_H

#include <SDL_opengl.h>
#define OBJ_ENTRY 256

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

  /* Sizer variables */
  double width, height, depth;
  double minX, minY, minZ;
  double maxX, maxY, maxZ;

  /* Mesh settings */
  GLdouble *vertices;
  GLdouble *color;
  GLdouble *faces;
  int entries, size;
  
}; 
typedef struct Object Object;

Object *newObject();
Object *objectInit(char **list);

char *objGetName(int index);


#endif

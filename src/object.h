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
  GLdouble *vertices;        // Vertices of the mesh
  GLdouble *color;           // Vertex color
  GLint *faces;              // Triangles hold three meshes
  int ventries, fentries,    // Count entries
    vsize, fsize;            // Size of the arrays
  
}; 
typedef struct Object Object;

/* Pixel access functions */
#define V(obj, i) (obj->vertices + i*3)
#define C(obj, i) (obj->color + i*3)
#define F(obj, i) (obj->faces + i*3)


Object *newObject();
Object *objectInit(char **list);

char *objGetName(int index);

/* Object mesh manipulation functions */
void objCheckArrays(Object *obj);
GLint objRegisterVertex(Object *obj,
			GLdouble x,
			GLdouble y,
			GLdouble z);
int objAddFace(Object *obj, GLint v1, GLint v2, GLint v3);

#endif

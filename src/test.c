#include <stdio.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <assert.h>
#include "elements.h"
#include "lua.h"
#include "globalindex.h"
#include "parser.h"
#include "debug.h"

Object *obj;

void initVideo()
{
  SDL_Init(SDL_INIT_VIDEO);
  SDL_SetVideoMode(640, 480, 16, SDL_OPENGL);
  glViewport(0, 0, 640, 480);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  float mat_specular[] = {1.0, 1.0, 1.0, 1.0};
  float mat_shininess[] = {50.0};
  float light_position[] = {1.0, 1.0, 1.0, 0.0};
  glShadeModel(GL_SMOOTH);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glEnable(GL_CULL_FACE);

  //glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

}


void game()
{
  SDL_Event ev;
  int done = 0;
  double angle = 0.0;

  glClearColor(1.0, 1.0, 1.0, 0.0);
  glColor3f(0.0, 0.0, 0.0);
  glEnable(GL_DEPTH_TEST);

  while (!done) {
    SDL_Delay(1000/30);
    while (SDL_PollEvent(&ev)) {
      switch (ev.type) {
      case SDL_QUIT:
	done = 1;
	break;
      }
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(cam->x, cam->y, cam->z,
	      cam->frontX, cam->frontY, cam->frontZ,
	      cam->upX, cam->upY, cam->upZ);
    glRotatef(angle, 0.0, 1.0, 0.0);
    angle+=0.3;
    draw(obj);
    SDL_GL_SwapBuffers();
  }
}

int main(int argc, char **argv)
{
  if (argc==1) {
    printf("lisp3d 0.0.1\n");
    printf("Usage: lisp3d worldfile\n");
    return 1;
  }

  printf("Init Video.. ");
  fflush(stdout);
  initVideo();
  printf("done\n");

  printf("Init Lua... ");
  fflush(stdout);
  initLua();
  printf("done\n");

  initGlobalIndex();
  initElements();

  printf("Parsing %s... ", argv[1]);
  fflush(stdout);
  obj = parse(argv[1]);
  printf("done\n");

  printf("Start Game!\n");
  game();

  return 0;
}

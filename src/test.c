/*
 * File test.c
 *
 * lisp3d is the legal property of Simon Goller (neosam@gmail.com).
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

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
  float mat_specular[] = {.2, .2, .2, 1.0};
  float mat_ambient[] = {.3, .3, .3, 1.0};
  float light_position[] = {5.0, 5.0, 15.0, 0.0};
  glShadeModel(GL_SMOOTH);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glEnable(GL_CULL_FACE);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glColorMaterial(GL_FRONT, GL_DIFFUSE);
  glEnable(GL_COLOR_MATERIAL);
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

void checkCamera()
{
  if (cam == NULL) {
    fprintf(stderr, "ERROR: No camera defined - abort\n");
    exit(1);
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
  checkCamera();
  game();

  return 0;
}

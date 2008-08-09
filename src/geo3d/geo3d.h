#ifndef MATRIXMULT_H
#define MATRIXMULT_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <SDL_opengl.h>

typedef GLdouble *vertex;
typedef GLdouble *matrix;

extern vertex v_buffer;
extern vertex v_buffer2;

extern matrix m_buffer;

void initGeo3d();

matrix newMatrix();
vertex newVertex();
matrix setMatrix(matrix, GLdouble, GLdouble, GLdouble, GLdouble,
                 GLdouble, GLdouble, GLdouble, GLdouble,
                 GLdouble, GLdouble, GLdouble, GLdouble,
                 GLdouble, GLdouble, GLdouble, GLdouble);
vertex setVertex(vertex, GLdouble, GLdouble, GLdouble, GLdouble);

/* Cross products */
vertex vertexXvertex(vertex, vertex, vertex);
vertex matrixXvertex(vertex, matrix, vertex);
matrix matrixXmatrix(matrix, matrix, matrix);

/* vector functions */
vertex addVertex(vertex, vertex, vertex);
vertex subVertex(vertex, vertex, vertex);
vertex normalVertex(vertex, vertex);
vertex multVertex(vertex, vertex, GLdouble);
GLdouble lengthVertex(vertex);
GLdouble dotProduct(vertex, vertex);
GLdouble radVertex(vertex, vertex);
GLdouble degVertex(vertex, vertex);

/* Create a matrix */
matrix createTransMatrix(matrix, GLdouble, GLdouble, GLdouble);
matrix createScaleMatrix(matrix, GLdouble, GLdouble, GLdouble);
matrix createXRotMatrix(matrix, GLdouble);
matrix createYRotMatrix(matrix, GLdouble);
matrix createZRotMatrix(matrix, GLdouble);
matrix createRotMatrix(matrix, GLdouble, vertex);

/* degree functions */
GLdouble rad2deg(GLdouble);
GLdouble deg2rad(GLdouble);

/* geometric vectors */
vertex normalTriangle(vertex, vertex, vertex, vertex);

/* Print functions */
void printVertex(vertex);
void printMatrix(matrix);

#endif

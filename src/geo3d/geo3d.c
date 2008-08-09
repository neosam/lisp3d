#include "geo3d.h"

vertex v_buffer;
vertex v_buffer2;

matrix m_buffer;

void initGeo3d()
{
    v_buffer = newVertex();
    v_buffer2 = newVertex();
    m_buffer = newMatrix();
}

matrix newMatrix()
{
    return (matrix) malloc(sizeof(GLdouble) * 16);
}

vertex newVertex()
{
    return (vertex) malloc(sizeof(GLdouble) * 4);
}

matrix setMatrix(matrix mat,
                 GLdouble x11, GLdouble x12, GLdouble x13, GLdouble x14,
                 GLdouble x21, GLdouble x22, GLdouble x23, GLdouble x24,
                 GLdouble x31, GLdouble x32, GLdouble x33, GLdouble x34,
                 GLdouble x41, GLdouble x42, GLdouble x43, GLdouble x44)
{
    /* Nice... 16 times the same :-D */
    mat[0] = x11;
    mat[1] = x21;
    mat[2] = x31;
    mat[3] = x41;
    mat[4] = x12;
    mat[5] = x22;
    mat[6] = x32;
    mat[7] = x42;
    mat[8] = x13;
    mat[9] = x23;
    mat[10] = x33;
    mat[11] = x43;
    mat[12] = x14;
    mat[13] = x24;
    mat[14] = x34;
    mat[15] = x44;

    return mat;
}

vertex setVertex(vertex ver,
                 GLdouble x1, GLdouble x2, GLdouble x3, GLdouble x4)
{
    ver[0] = x1;
    ver[1] = x2;
    ver[2] = x3;
    ver[3] = x4;

    return ver;
}

vertex vertexXvertex(vertex newver, vertex ver1, vertex ver2)
{
    newver[0] = ver1[1] * ver2[2] - ver1[2] * ver2[1];
    newver[1] = ver1[2] * ver2[0] - ver1[0] * ver2[2];
    newver[2] = ver1[0] * ver2[1] - ver1[1] * ver2[0];
    newver[3] = 0.0;

    return newver;
}

vertex matrixXvertex(vertex newver, matrix mat, vertex ver)
{
    setVertex(newver, 0.0, 0.0, 0.0, 0.0);
    int i, j;
    for(i = 0; i < 4; i++) {
        for(j = 0; j< 4; j++) {
            newver[i] += mat[4*j + i] * ver[j];
        }
    }

    return newver;
}

matrix matrixXmatrix(matrix newmat, matrix mat1, matrix mat2)
{
    newmat = setMatrix(newmat, 
                       0.0, 0.0, 0.0, 0.0,
                       0.0, 0.0, 0.0, 0.0,
                       0.0, 0.0, 0.0, 0.0,
                       0.0, 0.0, 0.0, 0.0);
    int i, j, k;
    for(i = 0; i < 4; i++) {
        for(j = 0; j< 4; j++) {
            for(k = 0; k < 4; k++) {
                newmat[4*j + i] += mat1[4*k + i] * mat2[4*j + k];
            }
        }
    }
    
    return newmat;
}


vertex addVertex(vertex newver, vertex ver1, vertex ver2)
{
    if (newver == ver1)
        newver = v_buffer;
    newver[0] = ver1[0] + ver2[0];
    newver[1] = ver1[1] + ver2[1];
    newver[2] = ver1[2] + ver2[2];
    newver[3] = 1.0;

    if (newver == v_buffer) {
        ver1 = (vertex) memcpy(ver1, newver, sizeof(GLdouble) * 4);
        newver = ver1;
    }

    return newver;
}

vertex subVertex(vertex newver, vertex ver1, vertex ver2)
{
    if (newver == ver1)
        newver = v_buffer;
    newver[0] = ver1[0] - ver2[0];
    newver[1] = ver1[1] - ver2[1];
    newver[2] = ver1[2] - ver2[2];
    newver[3] = 1.0;
    if (newver == v_buffer) {
        ver1 = (vertex) memcpy(ver1, newver, sizeof(GLdouble) * 4);
        newver = ver1;
    }

    return newver;
}

vertex normalVertex(vertex newver, vertex ver)
{
    newver = setVertex(newver, 0.0, 0.0, 0.0, 1.0);
    GLdouble factor;
   
    factor = sqrt(pow(ver[0], 2) + pow(ver[1], 2) + pow(ver[2], 2));
    newver[0] = ver[0] / factor;
    newver[1] = ver[1] / factor;
    newver[2] = ver[2] / factor;

    return newver;
}

vertex multVertex(vertex newver, vertex ver, GLdouble lambda)
{
    if (newver == ver) 
        newver = v_buffer;
    newver[0] = ver[0] * lambda;
    newver[1] = ver[1] * lambda;
    newver[2] = ver[2] * lambda;

    if (newver == v_buffer) {
        ver = (vertex) memcpy(ver, newver, sizeof(GLdouble) * 4);
        newver = ver;
    }

    return newver;
}

GLdouble lengthVertex(vertex ver)
{
    return sqrt(pow(ver[0], 2) + pow(ver[1], 2) + pow(ver[2], 2));
}

GLdouble dotProduct(vertex ver1, vertex ver2)
{
    return ver1[0] * ver2[0] + ver1[1] * ver2[1] + ver1[2] * ver2[2];
}

GLdouble radVertex(vertex ver1, vertex ver2)
{
    return acos(dotProduct(ver1, ver2) /
                lengthVertex(ver1) / lengthVertex(ver2));
}

GLdouble degVertex(vertex ver1, vertex ver2)
{
    return rad2deg(radVertex(ver1, ver2));
}


matrix createTransMatrix(matrix newmat, GLdouble x, GLdouble y, GLdouble z)
{
    newmat = setMatrix(newmat,
                       1.0, 0.0, 0.0, x,
                       0.0, 1.0, 0.0, y,
                       0.0, 0.0, 1.0, z,
                       0.0, 0.0, 0.0, 1.0);

    return newmat;
}

matrix createScaleMatrix(matrix newmat, GLdouble x, GLdouble y, GLdouble z)
{
    newmat = setMatrix(newmat,
                       x, 0.0, 0.0, 0.0,
                       0.0, y, 0.0, 0.0,
                       0.0, 0.0, z, 0.0,
                       0.0, 0.0, 0.0, 1.0);
    return newmat;
}

matrix createXRotMatrix(matrix newmat, GLdouble rad)
{
    newmat = setMatrix(newmat,
                       1.0, 0.0, 0.0, 0.0,
                       0.0, cos(rad), -sin(rad), 0.0,
                       0.0, sin(rad), cos(rad), 0.0,
                       0.0, 0.0, 0.0, 1.0);
    return newmat;
}

matrix createYRotMatrix(matrix newmat, GLdouble rad)
{
    newmat = setMatrix(newmat,
                       cos(rad), 0.0, sin(rad), 0.0,
                       0.0, 1.0, 0.0, 0.0,
                       -sin(rad), 0.0, cos(rad), 0.0,
                       0.0, 0.0, 0.0, 1.0);
    return newmat;
}

matrix createZRotMatrix(matrix newmat, GLdouble rad)
{
    newmat = setMatrix(newmat,
                       cos(rad), -sin(rad), 0.0, 0.0,
                       sin(rad), cos(rad), 0.0, 0.0,
                       0.0, 0.0, 1.0, 0.0,
                       0.0, 0.0, 0.0, 1.0);
    return newmat;
}

matrix createRotMatrix(matrix res, GLdouble a, vertex ver)
{
    vertex norm = normalVertex(v_buffer, ver);
    GLdouble cosa = cos(a);
    GLdouble sina = sin(a);
    GLdouble oneSubCosa = 1 - cos(a);
    GLdouble x = norm[0];
    GLdouble y = norm[1];
    GLdouble z = norm[2];

    /* Diagonal */
    res[0] = cosa * (1 - x*x) + x*x;
    res[5] = cosa * (1 - y*y) + y*y;
    res[10] = cosa * (1 - z*z) + z*z;

    /* xy */
    res[4] = -z * sina + x*y * (1 - cosa);
    res[1] = z * sina + x*y * (1 - cosa);
    
    /* xz */
    res[8] = y * sina + x*z * (1 - cosa);
    res[2] = -y * sina + x*z * (1 - cosa);
    
    /* yz */
    res[9] = -x * sina + y*z * (1 - cosa);
    res[6] = x * sina + y*z * (1 - cosa);

    /* bottom */
    res[03] = 0.0;
    res[07] = 0.0;
    res[11] = 0.0;
    res[15] = 1.0;

    /* right */
    res[12] = 0.0;
    res[13] = 0.0;
    res[14] = 0.0;

    return res;
}


GLdouble deg2rad(GLdouble rad)
{
    return rad * 2 * M_PI / 360.0;
}

GLdouble rad2deg(GLdouble deg)
{
    return deg * 360.0 / 2 / M_PI;
}


vertex normalTriangle(vertex normal, vertex ver1, vertex ver2, vertex ver3)
{
    subVertex(v_buffer, ver1, ver2);
    subVertex(v_buffer2, ver2, ver3);

    vertexXvertex(normal, v_buffer, v_buffer2);

    return normal;
}


void printVertex(vertex ver)
{
    printf("|%f|\n|%f|\n|%f|\n|%f|\n", ver[0], ver[1], ver[2], ver[3]); 
}

void printMatrix(matrix mat)
{
    printf("|%f %f %f %f|\n"
           "|%f %f %f %f|\n"
           "|%f %f %f %f|\n"
           "|%f %f %f %f|\n",
           mat[0], mat[4], mat[8], mat[12],
           mat[1], mat[5], mat[9], mat[13],
           mat[2], mat[6], mat[10], mat[14],
           mat[3], mat[7], mat[11], mat[15]);
}

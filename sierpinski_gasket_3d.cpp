#include <windows.h>
#include <GL/freeglut.h>
#include <stdlib.h>

GLfloat colors[4][3] = {
    {1.0, 0.0, 0.0}, // đỏ
    {0.0, 1.0, 0.0}, // xanh lá
    {0.0, 0.0, 1.0}, // xanh dương
    {0.0, 0.0, 0.0}  // đen
};

GLfloat v[4][3] = {
    {0.0, 0.0, 1.0},
    {0.0, 0.9428, -0.3333},
    {-0.8165, -0.4714, -0.3333},
    {0.8165, -0.4714, -0.3333}
};

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2, 2, -2, 2, -2, 2);

    glMatrixMode(GL_MODELVIEW);
}

void triangle(GLfloat *a, GLfloat *b, GLfloat *c) {
    glVertex3fv(a);
    glVertex3fv(b);
    glVertex3fv(c);
}

void tetra(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d) {
    glBegin(GL_TRIANGLES);

    glColor3fv(colors[0]);
    triangle(a, b, c);

    glColor3fv(colors[1]);
    triangle(a, c, d);

    glColor3fv(colors[2]);
    triangle(a, d, b);

    glColor3fv(colors[3]);
    triangle(b, d, c);

    glEnd();
}

void divide_tetra(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d, int m) {
    GLfloat mid[6][3];
    int j;

    if (m > 0) {

        for (j = 0; j < 3; j++) mid[0][j] = (a[j] + b[j]) / 2;
        for (j = 0; j < 3; j++) mid[1][j] = (a[j] + c[j]) / 2;
        for (j = 0; j < 3; j++) mid[2][j] = (a[j] + d[j]) / 2;
        for (j = 0; j < 3; j++) mid[3][j] = (b[j] + c[j]) / 2;
        for (j = 0; j < 3; j++) mid[4][j] = (c[j] + d[j]) / 2;
        for (j = 0; j < 3; j++) mid[5][j] = (b[j] + d[j]) / 2;

        divide_tetra(a, mid[0], mid[1], mid[2], m - 1);
        divide_tetra(mid[0], b, mid[3], mid[5], m - 1);
        divide_tetra(mid[1], mid[3], c, mid[4], m - 1);
        divide_tetra(mid[2], mid[5], mid[4], d, m - 1);
    }
    else {
        tetra(a, b, c, d);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glRotatef(30, 1, 1, 0);

    divide_tetra(v[0], v[1], v[2], v[3], 3);

    glFlush();
}

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Sierpinski Tetrahedron");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
}
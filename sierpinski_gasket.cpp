#include <windows.h>
#include <GL/glut.h>
#include <time.h>
#include <stdlib.h>

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(1.0, 0.0, 0.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 75.0, 0.0, 75.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

typedef float point2[2];

// void display() {
//     GLfloat vertices[3][2] = {
//         {0.0, 0.0},
//         {25.0, 50.0},
//         {50.0, 0.0}
//     };

//     GLfloat p[2] = {7.5, 5.0};
//     int j, k;

//     glClear(GL_COLOR_BUFFER_BIT);
//     glBegin(GL_POINTS);
//         for (k = 0; k < 500000; ++k) {
//             j = rand() % 3;
//             p[0] = (p[0] + vertices[j][0]) / 2.0;
//             p[1] = (p[1] + vertices[j][1]) / 2.0;
//             glVertex2fv(p);
//         }
//     glEnd();
//     glFlush();
// }

void triangle(point2 a, point2 b, point2 c) {
    glBegin(GL_TRIANGLES);
        glVertex2fv(a);
        glVertex2fv(b);
        glVertex2fv(c);
    glEnd();
}

void divide_triangle(point2 a, point2 b, point2 c, int n) {
    if(n == 0)
        triangle(a,b,c);

    else {
        point2 ab, ac, bc;

        for (int i = 0; i < 2; ++i) {
            ab[i] = (a[i] + b[i]) / 2;
            ac[i] = (a[i] + c[i]) / 2;
            bc[i] = (b[i] + c[i]) / 2;
        }

        divide_triangle(a, ab, ac, n - 1);
        divide_triangle(c, ac, bc, n - 1);
        divide_triangle(b, bc, ab, n - 1);
        }
}

void display() {
    point2 vertices[3] = {
    {0.0, 0.0},
    {25.0, 50.0},
    {50.0, 0.0}
    };
    glClear(GL_COLOR_BUFFER_BIT);
    divide_triangle(vertices[0], vertices[1], vertices[2], 5);
    glFlush();
}

int main(int argc, char** argv) {
    srand(time(NULL));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Sierpinski Triangle");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
}

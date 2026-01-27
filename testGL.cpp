// #include "stdafx.h"
#include "GL/glut.h"
#include "windows.h"
void reshape(int w, int h) {
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float aspect = (float)w / h;
    if (aspect >= 1.0f)
        gluOrtho2D(-aspect, aspect, -1, 1);
    else
        gluOrtho2D(-1, 1, -1/aspect, 1/aspect);

    glMatrixMode(GL_MODELVIEW);
}

void mydisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(168.0/255, 87.0/255, 255.0/255, 1);
    glColor3f(255.0/255, 255.0/255, 0);
    glBegin(GL_POLYGON);
    glutReshapeFunc(reshape);

    glVertex2f(-0.5, -0.5);
    glVertex2f(-0.5,  0.5);
    glVertex2f( 0.5,  0.5);
    glVertex2f( 0.5, -0.5);
    glEnd();
    glFlush();
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Simple");
    glutDisplayFunc(mydisplay);
    glutMainLoop();
}
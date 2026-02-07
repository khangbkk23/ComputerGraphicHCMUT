#include "windows.h"
#include "GL/glut.h"
#include "math.h"

#define PI 3.14159265358979323846

GLfloat angle = 0.0f;

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-75.0, 75.0, -75.0, 75.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void mydisplay() {
    float R = 50.0;
    
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
    glRotatef(angle, 0.0, 0.0, 1.0);

    for (int i = 0; i < 3; i++) {
        float startDeg = i * 120.0;
        float endDeg = startDeg + 10.0;

        float radStart = startDeg * PI / 180.0;
        float radEnd = endDeg * PI / 180.0;
        
        float x1 = R * cos(radStart);
        float y1 = R * sin(radStart);
        float x2 = R * cos(radEnd);
        float y2 = R * sin(radEnd);

        glColor3f(0.0, 1.0, 0.0);
        glBegin(GL_TRIANGLES);
            glVertex2f(0.0, 0.0);
            glVertex2f(x1, y1);
            glVertex2f(x2, y2);
        glEnd();

        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_LINE_LOOP);
            glVertex2f(0.0, 0.0);
            glVertex2f(x1, y1);
            glVertex2f(x2, y2);
        glEnd();
    }

    glPopMatrix();
    glutSwapBuffers();
}

void processTimer(int value) {
    angle += (GLfloat)value;
    if(angle > 360.0f) angle -= 360.0f;

    glutPostRedisplay();
    glutTimerFunc(100, processTimer, 10);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Problem 4: Rotating fan");

    init();
    glutDisplayFunc(mydisplay);
    glutTimerFunc(100, processTimer, 10);
    glutMainLoop();
    return 0;
}
#include <iostream>
#include <GL/glut.h>
#include <time.h>
#define PI 3.1415926
using namespace std;

void init() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-5.0, 5.0, -2.0, 8.0, -1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void drawAxis() {
    glColor3f(0,0,0);
    glBegin(GL_LINES);
    
    // trục X
    glVertex2f(-10, 0);
    glVertex2f(10, 0);

    // trục Y
    glVertex2f(0, -10);
    glVertex2f(0, 10);

    glEnd();
}

void drawGrid(){
    glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_LINES);
    for(int i = -10; i <= 10; ++i) {
        glVertex2f(i, -10);
        glVertex2f(i, 10);

        glVertex2f(-10, i);
        glVertex2f(10, i);
    }
	drawAxis();
    glEnd();
}

float v0[12][2] = {
	{0,0}, {0,2},
	{0.6,2}, {0.6,1.2},
	{1.4, 1.2}, {1.4,2},
	{2,2}, {2,0},
	{1.4,0}, {1.4,0.8},
	{0.6,0.8}, {0.6, 0}
};

float m[16] = {
	1, 0, 0, 0,
	0.3, 1, 0, 0,
	0, 0, 1, 0,
	3, 4, 0 , 1
};

void drawFigure0() {
	// glColor3f(1,0,0);
	glBegin(GL_LINE_LOOP);
	for(int i = 0; i < 12; ++i)
		glVertex2fv(v0[i]);
	glEnd();
}

void mydisplay(){
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	drawGrid();

	glPushMatrix();
	glColor3f(1,0,0);
	drawFigure0();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0,0,1);
	glTranslatef(4,5,0);
	glRotatef(60,0,0,1);
	drawFigure0();
	glPopMatrix();

	glPushMatrix();
	glLoadMatrixf(m);
	glColor3f(0,1,0);
	drawFigure0();
	glPopMatrix();

	glFlush();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Transformations");
	glutDisplayFunc(mydisplay);
	init();
	glutMainLoop();
	return 0;
}


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


void printMatrix(float*m) {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			printf("%8.4f ", m[i*4 + j]);
		}
		printf("\n");
	}
}

float Shear[16] = {
	1, -0.5, 0, 0,
	0,  1,   0, 0,
	0,  0,   1, 0,
	0,  0,   0, 1
};

void mydisplay(){
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	float modelviewMaxtrix[16];
	glColor3f(0,0,0);
	glPushMatrix();
	glTranslatef(-5,6,0);
	glScalef(5/2.0, 3/4.0, 1);
	glMultMatrixf(Shear);
	glTranslatef(-1, -1, 0);
	glGetFloatv(GL_MODELVIEW_MATRIX, modelviewMaxtrix);
	printMatrix(modelviewMaxtrix);
	glPopMatrix();
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


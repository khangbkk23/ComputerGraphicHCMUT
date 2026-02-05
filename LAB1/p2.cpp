#include "windows.h"
#include "GL/glut.h"
#include "math.h"
#define PI 3.14159265358979323846

void init() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-75.0, 75.0, -75.0, 75.0, -1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void display() {
	float R = 50.0;
	float x0 = 0.0;
	float y0 = 0.0;

	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINE_LOOP);

	for (int a = 0; a < 360; a += 10) {
		float rad = a * PI / 180.0;
		float x = x0 + R * cos(rad);
		float y = y0 + R * sin(rad);
		glVertex2f(x, y);
	}

	glEnd();
	glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Problem 2: Connected circle");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
}
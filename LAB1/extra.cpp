#include "windows.h"
#include "GL/glut.h"
#include "math.h"
#define PI 3.14159265358979323846
void init() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(0.0, 1.0, 0.5);

	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-150.0, 100.0, -150.0, 100.0, -1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void drawFan() {
	float R = 50.0;
	float x0 = 10.0;
	float y0 = 10.0;

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 1.0, 0.5);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x0, y0);
	for (int a = 0; a < 360; a+=5) {
		float rad = a * PI / 180.0;
		float x = x0 + R * cos(rad);
		float y = y0 + R * sin(rad);
		glVertex2f(x, y); 
	}
	glEnd();
	
	glColor3f(0.0,0.0,0.0);

	glBegin(GL_LINE_LOOP);
	for (int a = 0; a < 360; a += 5) {
            float rad = a * PI / 180.0;
            float x = x0 + R * cos(rad);
            float y = y0 + R * sin(rad);
            glVertex2f(x, y);
        }
    glEnd();
	
	glColor3f(1.0,0.5,0.0);
	glBegin(GL_LINES);
	for(int a = 0; a < 360; a+=5) {
		float rad = a * PI / 180.0;
		float x = x0 + R * cos(rad);
		float y = y0 + R * sin(rad);

		glVertex2f(x0,y0);
		glVertex2f(x, y);
	}
	glEnd();
}

void drawParallelogram() {
	glColor3f(0.2, 0.2, 1.0);

	glBegin(GL_QUADS);
		glVertex2f(-140.0, -80.0);
		glVertex2f(-80.0, -80.0);
		glVertex2f(-60.0, -60.0);
		glVertex2f(-120.0, -60.0);
	glEnd();

	glColor3f(1.0,0.0,0.0);
	glLineWidth(2.0);
	glBegin(GL_LINE_LOOP);
        glVertex2f(-140.0, -80.0);
		glVertex2f(-80.0, -80.0);
		glVertex2f(-60.0, -60.0);
		glVertex2f(-120.0, -60.0);
	glEnd();
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT);

	drawFan();
	drawParallelogram();

	glFlush();
}

int main(int argc, char**argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Draw fan with parallelogram");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
}
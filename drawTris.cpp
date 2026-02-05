#include "windows.h"
#include "GL/glut.h"
void init() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 50.0, 0, 50.0);
	glMatrixMode(GL_MODELVIEW);
}
void figure(){
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_TRIANGLE_STRIP);
		glVertex2f(-0.5, 1.0);
		glVertex2f( 0.5, 1.0);
		glVertex2f(-0.5, 0.0);
		glVertex2f(-0.5, 0.0);
		glVertex2f( 0.5, 1.0);
		glVertex2f( 0.5, 0.0);
		glVertex2f(-0.5, -1.0);
		glVertex2f(-0.5, 0.0);
		glVertex2f( 0.5, 0.0)	;
		glVertex2f( 0.5, 0.0);
		glVertex2f(-0.5, -1.0);
		glVertex2f( 0.5, -1.0);
	glEnd();
	glFlush();
	// lẻ thì sẽ không vẽ tiếp cái điểm đó
}

void drawFan() {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(0.0, 0.0);   // tâm
		glVertex2f(1.0, 0.0);
		glVertex2f(0.7, 0.7);
		glVertex2f(0.0, 1.0);
		glVertex2f(-0.7, 0.7);
		glVertex2f(-1.0, 0.0);
		glVertex2f(-0.7, -0.7);
		glVertex2f(0.0, -1.0);
		glVertex2f(0.7, -0.7);
		glVertex2f(1.0, 0.0); // đóng quạt
	glEnd();
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	    glutInitWindowSize(600, 600);
    glutCreateWindow("Simple");

    init();
    glutDisplayFunc(drawFan);
    glutMainLoop();
}
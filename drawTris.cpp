#include "windows.h"
#include "GL/glut.h"
void init() {
	glClearColor(0.0, 0.0, 0.0, 1.0); // Black background
	glColor3f(1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
}
void figure(){
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_TRIANGLE_STRIP); // giảm tải cho đường ống đồ hoạ #STRIP"
		glVertex2f(-0.5, 1.0);
		glVertex2f( 0.5, 1.0);
		glVertex2f(-0.5, 0.0);
		glVertex2f(-0.5, 0.0);
		glVertex2f( 0.5, 1.0);
		glVertex2f( 0.5, 0.0);
		glVertex2f(-0.5, -1.0);
		glVertex2f(-0.5, 0.0);
		glVertex2f( 0.5, 0.0);
		glVertex2f( 0.5, 0.0);
		glVertex2f(-0.5, -1.0);
		glVertex2f( 0.5, -1.0);
	glEnd();
	glFlush();
	// lẻ thì sẽ không vẽ tiếp cái điểm đó
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	    glutInitWindowSize(600, 600);
    glutCreateWindow("Simple");

    init();
    glutDisplayFunc(figure);
    glutMainLoop();
}
#include <windows.h>
#include <GL/glut.h>

void init() {
	glClearColor(0.0, 0.0, 0.0, 1.0); // Black background
	glColor3f(1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 4.0, 0.0, 4.0, -1.0, 1.0);
}

void mydisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
		glVertex2f(3,1);
		glVertex2f(1,1);
		glVertex2f(1,3);
	glEnd();
	glFlush();
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Simple");

    init();
    glutDisplayFunc(mydisplay);
    glutMainLoop();
}


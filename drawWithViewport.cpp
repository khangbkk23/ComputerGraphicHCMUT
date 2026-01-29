#include "windows.h"
#include <GL/glut.h>
void drawfigure() {
	glBegin(GL_POLYGON);
		glVertex2f(-2.0, 2.0);
		glVertex2f(-2.0, 2.0);

}

int main(int argc, char* argv[]){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Simple");
	glutMainLoop();
}
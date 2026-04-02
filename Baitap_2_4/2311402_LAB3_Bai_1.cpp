#include <windows.h>
#include <gl\glut.h>
#include <tchar.h>
#include <iostream>

using namespace std;

#define	WINDOW_LEFT		-10
#define	WINDOW_RIGHT		 10
#define	WINDOW_BOTTOM		-10
#define	WINDOW_TOP		 10

void myInit(){
	glClearColor(1.0,1.0,1.0,0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(WINDOW_LEFT, WINDOW_RIGHT, WINDOW_BOTTOM, WINDOW_TOP);
}

void drawGrid(){
	glColor3f(0.6f, 0.6f, 0.6f);
	glLineWidth(1.0);

	glBegin(GL_LINES);
		for(int i = WINDOW_LEFT; i<=WINDOW_RIGHT; i++){
			glVertex2i(i, WINDOW_BOTTOM);
			glVertex2i(i, WINDOW_TOP);
		}
		for(int i = WINDOW_BOTTOM; i<=WINDOW_TOP; i++){
			//Code here 1
			///////////////
			glVertex2i(WINDOW_LEFT, i);
			glVertex2i(WINDOW_RIGHT, i);
		}
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	glLineWidth(5.0);

	glBegin(GL_LINES);
		glVertex2i(WINDOW_LEFT, 0);
		glVertex2i(WINDOW_RIGHT, 0);
		glVertex2i(0, WINDOW_BOTTOM);
		glVertex2i(0, WINDOW_TOP);
	glEnd();
}
void drawHouse() {
	glLineWidth(3.0);
	//Code here 2
	glBegin(GL_LINE_LOOP);
		glVertex2f(0.0, 0.0);
		glVertex2f(0.0, 2.0);
		glVertex2f(0.5, 2.5);
		glVertex2f(0.5, 4.0);
		glVertex2f(1.5, 4.0);
		glVertex2f(1.5, 3.5);
		glVertex2f(0.5, 2.5);
		glVertex2f(2.0, 4.0);
		glVertex2f(4.0, 2.0);
		glVertex2f(4.0, 0.0);
	glEnd();
}

void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    drawGrid();

    // Hình 1
    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);
    drawHouse();
    glPopMatrix();

    // Hình 2
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 1.0f);
    glTranslatef(4.0f, 3.0f, 0.0f);
    drawHouse();
    glPopMatrix();

    // Hình 3
    glPushMatrix();
    glColor3f(1.0f ,0.0f ,1.0f);
    glTranslatef(2.0f,-3.0f,0.0f);
	glScalef(1.0f,1.5f,1.0f);
    drawHouse();
    glPopMatrix();

	// Hình 4
	glPushMatrix();
    glColor3f(1.0f, 0.5f, 0.0f);
    glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
    glTranslatef(2.0f, 0.0f, 0.0f);
    drawHouse();
    glPopMatrix();

	// Hình 5
	glPushMatrix();
    glColor3f(0.0f, 1.0f, 0.0f);
    glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
    glScalef(1.5f, 1.5f, 1.0f);
	drawHouse();
	glPopMatrix();

    glFlush();
}

int main(int argc, _TCHAR* argv[]) {
	glutInit(&argc, (char**)argv); //initialize the tool kit
	glutInitDisplayMode(GLUT_SINGLE |GLUT_RGB); //set the display mode
	glutInitWindowSize(650, 650); //set window size
	glutInitWindowPosition(0, 0); // set window position on screen
	glutCreateWindow("LAB-Transformation");//open the screen window

	myInit();
	glutDisplayFunc(myDisplay);
	glutMainLoop();
	return 0;
}
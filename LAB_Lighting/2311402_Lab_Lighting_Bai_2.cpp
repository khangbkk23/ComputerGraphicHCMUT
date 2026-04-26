#include <windows.h>
#include <math.h>
#include <gl\glut.h>
#include <tchar.h>

const int screenWidth = 650;
const int screenHeight = 650;


void init() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.2, 1.2, -1.2, 1.2, 0.1, 100);
}

void setLight() {
	const GLfloat leftLightDiffColor[] = { 1.0f, 0.0f, 0.0f, 1.0f };
    const GLfloat leftLightSpecColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
    const GLfloat leftLightAmbColor[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
    const GLfloat leftLightPos[]       = { -5.0f, 0.0f, 0.0f, 0.0f };

    const GLfloat rightLightDiffColor[] = { 0.0f, 0.0f, 1.0f, 1.0f };
    const GLfloat rightLightSpecColor[] = { 1.0f, 0.0f, 1.0f, 1.0f };
    const GLfloat rightLightAmbColor[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
    const GLfloat rightLightPos[]       = { 5.0f, 0.0f, 0.0f, 0.0f };

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);

	//set up right light
	glLightfv(GL_LIGHT0, GL_POSITION, rightLightPos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, rightLightAmbColor);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, rightLightDiffColor);
	glLightfv(GL_LIGHT0, GL_SPECULAR, rightLightSpecColor);
	glEnable(GL_LIGHT0);

	//set up left light
	glLightfv(GL_LIGHT1, GL_POSITION, leftLightPos);
	glLightfv(GL_LIGHT1, GL_AMBIENT, leftLightAmbColor);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, leftLightDiffColor);
	glLightfv(GL_LIGHT1, GL_SPECULAR, leftLightSpecColor);
	glEnable(GL_LIGHT1);

}

void display() {
	glClearColor(1.0,1.0,1.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	setLight();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 6.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	GLfloat ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
    GLfloat diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	GLfloat shiness = 100.8;


	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiness);

	glutSolidSphere(1.0, 100, 100);

	glutSwapBuffers();
	glFlush();

	glFlush();
}

int main(int argc, _TCHAR* argv[]) {
	glutInit(&argc, (char**)argv); //initialize the tool kit
	glutInitDisplayMode(GLUT_SINGLE |GLUT_RGB |GLUT_DEPTH);//set the display mode
	glutInitWindowSize(screenWidth, screenHeight); //set window size
	glutInitWindowPosition(0, 0); // set window position on screen
	glutCreateWindow("Lab Lighting - Bai 2"); // open the screen window

	glutDisplayFunc(display);

	init();
	glEnable(GL_DEPTH_TEST);

	glutMainLoop();
	return 0;
}

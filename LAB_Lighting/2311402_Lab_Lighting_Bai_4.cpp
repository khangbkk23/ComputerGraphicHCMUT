#include <windows.h>
#include <math.h>
#include <gl\glut.h>
#include <iostream>
#include <tchar.h>

using namespace std;

#define		PI	3.1415926

int		nHeight = 600;
int		nWidth = 600;

const GLfloat lightColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat lightAmbColor[] = { 0.1f, 0.1f, 0.1f, 1.0f};
const GLfloat lightPos[] = { 5.0, 0.0, 0.0, 0.0 };

GLboolean m_lightOn = GL_TRUE;

GLboolean m_smoothshadeModeOn = GL_TRUE;

float	m_angle = 0.0;

void myInit() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
	glClearColor(0, 0, 0, 1);

	//set up the light
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbColor);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightColor);
}

void mySetup(int width, int height) {
	glViewport(0, 0, width, height);		// reset the viewport to new dimensions
	glMatrixMode(GL_PROJECTION);			// set projection matrix current matrix
	glLoadIdentity();						// reset projection matrix

	// calculate aspect ratio of window
	gluPerspective(60.0f,(GLfloat)width/(GLfloat)height,1.0f,1000.0f);

	glMatrixMode(GL_MODELVIEW);				// set modelview matrix
	glLoadIdentity();						// reset modelview matrix

}

void setMaterial(float ar, float ag, float ab,
				float dr, float dg, float db,
				float sr, float sg, float sb) {
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
	GLfloat	shiness = 100.8;

	ambient[0] = ar; ambient[1] = ag; ambient[2] = ab; ambient[3] = 1;
	diffuse[0] = dr; diffuse[1] = dg; diffuse[2] = db; diffuse[3] = 1;
	specular[0]= sr; specular[1]= sg; specular[2]= sb; specular[3]= 1;

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiness);
}

void myDisplay() {
    glClearColor(0.0,0.0,0.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glLoadIdentity();
    gluLookAt(6.0, 4.0, 6.0, 0.0, 0.0, 2.0, 0.0, 1.0, 0.0);

    glRotatef(m_angle, 0.0, 1.0, 0.0);

    //light
    if(m_lightOn)
        glEnable(GL_LIGHT0);
    else
        glDisable(GL_LIGHT0);


    if(m_smoothshadeModeOn)
        glShadeModel(GL_SMOOTH);
    else
        glShadeModel(GL_FLAT);

    GLUquadricObj* obj;

    //draw the chest
    setMaterial(0.1, 0.1, 0.1,
                0, 1, 0,
                1, 1, 1);
    glPushMatrix();
    glutSolidSphere(1, 100, 100);
    glPopMatrix();

    //draw the abdomen
    setMaterial(0.1, 0.1, 0.1,
                1, 0, 0,
                1, 1, 1);
    glPushMatrix();
    glTranslated(0.0, -1.8, 0.0);
    glutSolidSphere(1.3, 20, 20);
    glPopMatrix();

    //draw the head
    setMaterial(0.1, 0.1, 0.1,
                1, 1, 0,
                1, 1, 1);
    glPushMatrix();
    glTranslated(0.0, 1.4, 0.0);
    glutSolidSphere(0.65, 50, 50);
    glPopMatrix();

    //draw nose
    setMaterial(0.1, 0.1, 0.1,
                1, 0, 0,
                1, 1, 1);
    glPushMatrix();
    glTranslated(0.0, 1.4, 0.65);
    glutSolidSphere(0.15, 20, 20);
    glPopMatrix();

    //draw left eye
    setMaterial(0.1, 0.1, 0.1,
                0, 1, 0,
                1, 1, 1);
    glPushMatrix();
    glTranslated(-0.25, 1.6, 0.55);
    glutSolidSphere(0.1, 20, 20);
    glPopMatrix();

    //draw right eye
    glPushMatrix();
    glTranslated(0.25, 1.6, 0.55);
    glutSolidSphere(0.1, 20, 20);
    glPopMatrix();

    //draw the hat
    setMaterial(0.1, 0.1, 0.1,
                1, 0, 0,
                1, 1, 1);
    glPushMatrix();
    glTranslated(0.0, 1.8, 0.0);
    glRotated(-90, 1.0, 0.0, 0.0);
    glutSolidCone(0.5, 1.5, 30, 20);
    glPopMatrix();

    //draw left hand
    setMaterial(0.1, 0.1, 0.1,
                1, 0, 1,
                1, 1, 1);
    glPushMatrix();
    glTranslated(-1.0, 0.2, 0.0);
    glRotated(-90, 0.0, 1.0, 0.0);
    obj = gluNewQuadric();
    gluQuadricDrawStyle(obj, GLU_FILL);
    gluCylinder(obj, 0.25, 0.25, 1.5, 30, 10);
    gluDeleteQuadric(obj);
    glPopMatrix();

    //draw right hand
    glPushMatrix();
    glTranslated(1.0, 0.2, 0.0);
    glRotated(90, 0.0, 1.0, 0.0);
    obj = gluNewQuadric();
    gluQuadricDrawStyle(obj, GLU_FILL);
    gluCylinder(obj, 0.25, 0.25, 1.5, 30, 10);
    gluDeleteQuadric(obj);
    glPopMatrix();

    //draw noel tree
    setMaterial(0.1, 0.1, 0.1,
                0, 1, 0,
                1, 1, 1);

    glPushMatrix();
    glTranslated(0.0, 0.0, 5.0);
    glTranslated(0.0, -1.0, 0.0);
    glRotated(-90, 1.0, 0.0, 0.0);
    glutSolidCone(0.8, 2.5, 30, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0.0, 0.0, 5.0);
    glTranslated(0.0, 1.0, 0.0);
    glRotated(-90, 1.0, 0.0, 0.0);
    glutSolidCone(0.8, 2.5, 30, 20);
    glPopMatrix();

    setMaterial(0.1, 0.1, 0.1,
                1, 0.5, 0,
                1, 1, 1);
    glPushMatrix();
    glTranslated(0.0, 0.0, 5.0);
    glTranslated(0.0, -3.0, 0.0);
    glRotated(-90, 1.0, 0.0, 0.0);
    obj = gluNewQuadric();
    gluQuadricDrawStyle(obj, GLU_FILL);
    gluCylinder(obj, 0.4, 0.4, 3, 30, 10);
    glPopMatrix();
    gluDeleteQuadric(obj);

    glutSwapBuffers();
    glFlush();
}

void myReshape(int cx, int cy) {
	mySetup(cx, cy);
	myDisplay();
}

void myIdle() {
	float	dt = 0.2;
	m_angle = m_angle + dt;
	if(m_angle >= 360)
		m_angle = 0;
	myDisplay();
}

void myKeyboard(unsigned char theKey, int mouseX, int mouseY) {
	switch(theKey) {
	case 'o':
		m_lightOn = !m_lightOn;
		break;
	case 's':
		m_smoothshadeModeOn = !m_smoothshadeModeOn;
		break;
	default:
		break;
	}
}

int main(int argc, _TCHAR* argv[]) {
	cout << "Press following key to control the program\n\n";
	cout << "<o>. Turn on/off the light\n";
	cout << "<s>. Turn on/off smooth shading\n";

	glutInit(&argc, (char**)argv); //initialize the tool kit
	glutInitDisplayMode(GLUT_SINGLE |GLUT_RGB |GLUT_DEPTH);//set the display mode
	glutInitWindowSize(nWidth, nHeight); //set window size
	glutInitWindowPosition(0, 0); // set window position on screen
	glutCreateWindow("Lab Lighting - Bai 4"); // open the screen window


	myInit();

	glutReshapeFunc(myReshape);
	glutDisplayFunc(myDisplay);
	glutIdleFunc(myIdle);
	glutKeyboardFunc(myKeyboard);

	glutMainLoop();
	return 0;
}
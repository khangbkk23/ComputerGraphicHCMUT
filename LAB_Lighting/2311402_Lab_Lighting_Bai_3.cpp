#include <windows.h>
#include <math.h>
#include <gl\glut.h>
#include <iostream>
#include <tchar.h>

using namespace std;

const int screenWidth = 650;
const int screenHeight = 650;

float	m_angle = 0.0;
GLboolean m_leftlightOn = GL_TRUE;
GLboolean m_rightlightOn = GL_TRUE;

GLboolean m_smoothshadeModeOn = GL_FALSE;

void init()
{
	glEnable(GL_NORMALIZE);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.2, 1.2, -1.2, 1.2, 0.1, 100);
}
void setLight()
{
	const GLfloat leftLightDiffColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	const GLfloat leftLightSpecColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	const GLfloat leftLightAmbColor[] = { 0.1f, 0.1f, 0.1f, 1.0f};
	const GLfloat leftLightPos[] = { 0.0, 0.0, -1.0, 0.0 };

	const GLfloat rightLightDiffColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	const GLfloat rightLightSpecColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	const GLfloat rightLightAmbColor[] = { 0.1f, 0.1f, 0.1f, 1.0f};
	const GLfloat rightLightPos[] = { 0.0, 0.0, 1.0, 0.0 };

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
void setMaterial(float ar, float ag, float ab,
				float dr, float dg, float db,
				float sr, float sg, float sb)
{
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

void display()
{
	glClearColor(1.0,1.0,1.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	setLight();

	if(m_rightlightOn)
		glEnable(GL_LIGHT0);
	else
		glDisable(GL_LIGHT0);

	if(m_leftlightOn)
		glEnable(GL_LIGHT1);
	else
		glDisable(GL_LIGHT1);

	if(m_smoothshadeModeOn)
		glShadeModel(GL_SMOOTH);
	else
		glShadeModel(GL_FLAT);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, -4.0, 15.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glRotatef(m_angle, 0.0, 1.0, 0.0);

	glPushMatrix();
	setMaterial(0.1, 0.1, 0.1,
		       1.0, 0.0, 0.0,
			   1.0, 1.0, 1.0);
	glutSolidSphere(0.2, 20, 20);
	glPopMatrix();


	setMaterial(0.1, 0.1, 0.1,
		       0.0, 0.0, 1.0,
			   1.0, 1.0, 1.0);
	glPushMatrix();
	glTranslatef(0, 0.5, 0);
	glRotatef(-90, 1, 0, 0);
	glutSolidCone(0.2, 0.4, 20, 30);
	glPopMatrix();

	GLUquadricObj* obj;

	setMaterial(0.1, 0.1, 0.1,
		       0.0, 1.0, 0.0,
			   1.0, 1.0, 1.0);
	glPushMatrix();
	glTranslatef(-0.4, 0, 0);
	glRotatef(-90, 0, 1, 0);
	obj = gluNewQuadric();
	gluQuadricDrawStyle(obj, GLU_FILL);
	gluCylinder(obj, 0.1, 0.1, 0.6, 30, 10);
	glPopMatrix();

	setMaterial(0.1, 0.1, 0.1,
		       1.0, 0.0, 1.0,
			   1.0, 1.0, 1.0);
	glPushMatrix();
	glTranslatef(0.4, 0, 0);
	glRotatef(90, 0, 1, 0);
	obj = gluNewQuadric();
	gluQuadricDrawStyle(obj, GLU_FILL);
	gluCylinder(obj, 0.2, 0.06, 0.6, 30, 10);
	glPopMatrix();

	glutSwapBuffers();
	glFlush();
}

void myIdle()
{
	float	dt = 0.05;
	m_angle = m_angle + dt;
	if(m_angle >= 360)
		m_angle = 0;
	display();
}

void myKeyboard(unsigned char theKey, int mouseX, int mouseY)
{
	switch(theKey)
	{
	case 'r':
		m_rightlightOn = !m_rightlightOn;
		break;
	case 'l':
		m_leftlightOn = !m_leftlightOn;
		break;
	case 's':
		m_smoothshadeModeOn = !m_smoothshadeModeOn;
		break;
	default:
		break;
	}
}

int main(int argc, _TCHAR* argv[])
{
	cout << "<r>. Turn on/off right light\n";
	cout << "<l>. Turn on/off left light\n";
	cout << "<s>. Turn on/off smooth shading\n";

	glutInit(&argc, (char**)argv); //initialize the tool kit
	glutInitDisplayMode(GLUT_SINGLE |GLUT_RGB |GLUT_DEPTH);//set the display mode
	glutInitWindowSize(screenWidth, screenHeight); //set window size
	glutInitWindowPosition(0, 0); // set window position on screen
	glutCreateWindow("Lab Lighting - Bai 3"); // open the screen window

	glutDisplayFunc(display);
	glutIdleFunc(myIdle);
	glutKeyboardFunc(myKeyboard);

	init();
	glEnable(GL_DEPTH_TEST);

	glutMainLoop();
	return 0;
}

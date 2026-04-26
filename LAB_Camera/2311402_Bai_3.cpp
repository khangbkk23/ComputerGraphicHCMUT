#include <iostream>
#include <windows.h>
#include <gl\glut.h>
#include <math.h>
#include <tchar.h>

using namespace std;

#define PI		3.1415926

#define		DEG2RAD(x) (x*PI)/180.0f

void myDisplay();

int		screenWidth = 600;
int		screenHeight= 600;

float camera_angle;
float camera_height;
float camera_dis;
float camera_X, camera_Y, camera_Z;
float lookAt_X, lookAt_Y, lookAt_Z;

bool	b4View = false;

void mySetupCameraVolume(int nType) {
	if (nType == 4) {
		glMatrixMode(GL_PROJECTION);		
		glLoadIdentity();					

		
		gluPerspective(60.0f,(GLfloat)screenWidth/(GLfloat)screenHeight,1.0f,1000.0f);
	} else if(nType == 1) {
		glMatrixMode(GL_PROJECTION);			
		glLoadIdentity();						
		glOrtho(-5, 5, -5, 5, -1000, 1000);
	} else if(nType == 2) {
		glMatrixMode(GL_PROJECTION);			
		glLoadIdentity();						
		glOrtho(-5, 5, -5, 5, -1000, 1000);
	} else if(nType == 3) {
		glMatrixMode(GL_PROJECTION);			
		glLoadIdentity();						
		glOrtho(-5, 5, -5, 5, -1000, 1000);
	}
}

void changeCameraPos() {
	camera_X = sin(DEG2RAD(camera_angle))*camera_dis;
	camera_Y = camera_height;
	camera_Z = cos(DEG2RAD(camera_angle))*camera_dis;

	myDisplay();
}


void mySpecialKeyboard(int theKey, int mouseX, int mouseY) {
	//code here
	switch(theKey) {
	case GLUT_KEY_UP:
		camera_height += 0.1;
		changeCameraPos();
		break;
	case GLUT_KEY_DOWN:
		camera_height -= 0.1;
		changeCameraPos();
		break;
	case GLUT_KEY_LEFT:
		camera_angle += 0.1;
		changeCameraPos();
		break;
	case GLUT_KEY_RIGHT:
		camera_angle -= 0.1;
		changeCameraPos();
		break;
	}
}

void myKeyboard(unsigned char key, int x, int y) {
    switch(key) {
	//Code here
	case 'V':
	case 'v':
		b4View = !b4View;
		break;
	case '+':
		camera_dis += 0.1;
		changeCameraPos();
		break;
	case '-':
		camera_dis -= 0.1;
		changeCameraPos();
		break;
	}
    glutPostRedisplay();
}

void DisplayOneView(int nType, int left, int right, int top, int bottom) {
	mySetupCameraVolume(nType);
	glViewport(left, top, right - left, bottom - top);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//code here
	if(nType == 1)
		gluLookAt(0, camera_dis, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
	else if(nType == 2)
		gluLookAt(0, 0.0, camera_dis, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	else if(nType == 3)
		gluLookAt(camera_dis, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	else
		gluLookAt(camera_X, camera_Y, camera_Z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	//

	glColor3f(0, 0, 1);
	glutSolidTeapot(2);
}

void myDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (b4View == false) {
		DisplayOneView(4, 0, screenWidth, 0, screenHeight);
	}
	else {
		//code here
		DisplayOneView(1, 0, screenWidth/2, 0, screenHeight/2);
		DisplayOneView(2, 0, screenWidth/2, screenHeight/2, screenHeight);
		DisplayOneView(3, screenWidth/2, screenWidth, screenHeight/2, screenHeight);
		DisplayOneView(4, screenWidth/2, screenWidth, 0, screenHeight/2);
		//
	}

	glFlush();
    glutSwapBuffers();
}

void myInit() {
	float	fHalfSize = 3;

	camera_angle = 0.0;
	camera_height = 2.0;
	camera_dis = 11;
	camera_X = sin(DEG2RAD(camera_angle))*camera_dis;
	camera_Y = camera_height;
	camera_Z = cos(DEG2RAD(camera_angle))*camera_dis;

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void setLight() {
	GLfloat	lightIntensity[]={0.7f, 0.7f, 0.7f, 1.0f};
	GLfloat light_position[]={10, 10, 20.0f, 0.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);

	GLfloat light_position1[]={10, 10, -20.0f, 0.0f};
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightIntensity);

	GLfloat light_position2[]={0, -10, 0.0f, 0.0f};
	glLightfv(GL_LIGHT2, GL_POSITION, light_position2);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, lightIntensity);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	glShadeModel(GL_SMOOTH);
}
void setMaterial() {
	GLfloat	mat_ambient[]={0.7f, 0.7f, 0.7f, 1.0f};
	GLfloat	mat_diffuse[]={1.0f, 0.0f, 0.0f, 1.0f};
	GLfloat	mat_specular[]={1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat mat_shininess[] = {50.0f};

	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE, mat_diffuse);
}

int main(int argc, _TCHAR* argv[]) {
cout << "V, v: to switch between 1 and 4 views." << endl;
cout << "+   : to increase camera distance." << endl;
cout << "-   : to decrease camera distance." << endl;
cout << "up arrow  : to increase camera height." << endl;
cout << "down arrow: to decrease camera height." << endl;
cout << "<-        : to rotate camera clockwise." << endl;
cout << "->        : to rotate camera counterclockwise." << endl;

glutInit(&argc, (char**)argv); //initialize the tool kit
glutInitDisplayMode(GLUT_DOUBLE |GLUT_RGB |GLUT_DEPTH);
glutInitWindowSize(screenWidth, screenHeight); //set window size
glutInitWindowPosition(100, 100);
glutCreateWindow("Lab Camera"); // open the screen window

glEnable(GL_DEPTH_TEST);
myInit();
setLight();
setMaterial();

glutKeyboardFunc(myKeyboard);
glutDisplayFunc(myDisplay);
glutSpecialFunc(mySpecialKeyboard);

glutMainLoop();
return 0;
}

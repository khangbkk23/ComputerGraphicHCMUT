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
	// glEnable(GL_LIGHT2);
	glShadeModel(GL_SMOOTH);
}

void setMaterial() {
	GLfloat	mat_ambient[]={0.7f, 0.7f, 0.7f, 1.0f};
	GLfloat	mat_diffuse[]={1.0f, 0.0f, 0.0f, 1.0f};
	GLfloat	mat_specular[]={1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat mat_shininess[] = {50.0f};

	glMaterialfv(GL_FRONT,GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT,GL_DIFFUSE, mat_diffuse);
}

void setCamera() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// // Hinh 1
	// gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	// // Hinh 2
	// gluLookAt(0.0, 0.0, -10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	// // Hinh 3
	// gluLookAt(10.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	// // Hinh 4
	// gluLookAt(0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    // // Hinh 5
	// gluLookAt(0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    // // Hinh 6
	// gluLookAt(0.0, -10.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 0.0);
    // // Hinh 7
	// gluLookAt(10.0, 10.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    // // Hình 8
    // gluLookAt(-10.0, 10.0, -10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    // // Hình 9
    // gluLookAt(10.0, -5.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    // Hình 10
    gluLookAt(10.0, -5.0, 10.0, 0.0, -0.5, 0.0, 0.0, 1.0, 0.0);
}

void drawAxis() {
	glDisable(GL_LIGHTING);

	float	xmax = 1.0, ymax = 1.0, zmax = 1.0;
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINES);
		glVertex3f(-xmax, 0, 0);
		glVertex3f(xmax, 0, 0);
		glVertex3f(0, -ymax, 0);
		glVertex3f(0, ymax, 0);
		glVertex3f(0, 0, -zmax);
		glVertex3f(0, 0, zmax);
	 glEnd();


	glColor3f(0.0, 0.0, 0.0);
	void * font = GLUT_BITMAP_TIMES_ROMAN_24;

	glRasterPos3f(1.0, 0, 0);
	glutBitmapCharacter(font, 'X');

	glRasterPos3f(0, 1.0, 0);
	glutBitmapCharacter(font, 'Y');

	glRasterPos3f(0, 0, 1.0);
	glutBitmapCharacter(font, 'Z');
}

void display() {
	glClearColor(1.0,1.0,1.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );


	setCamera();
	drawAxis();
	setLight();

	setMaterial();

	glutSolidTeapot(0.25);

	glFlush();
}


int main(int argc, _TCHAR* argv[]) {
	glutInit(&argc, (char**)argv); //initialize the tool kit
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB |GLUT_DEPTH);
	glutInitWindowSize(screenWidth, screenHeight); //set window size
	glutInitWindowPosition(0, 0); // set window position on screen
	glutCreateWindow("Lab Camera"); // open the screen window

	glutDisplayFunc(display);

	init();
	glEnable(GL_DEPTH_TEST);

	glutMainLoop();
	return 0;
}
// Làm bài 1 và bài 3 (thay đổi tham số đọc kĩ theo đặc tả)
// Bài 1 hay thi trắc nghiệm
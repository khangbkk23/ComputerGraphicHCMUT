#include <windows.h>
#include <math.h>
#include <GL/glut.h>
#include <tchar.h>

const int screenWidth = 700;
const int screenHeight = 700;

void init(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.2, 1.2, -1.2, 1.2, 0.1, 100);
}
void setLight(){
	GLfloat	lightIntensity[]={0.7f, 0.7f, 0.7f, 1.0f};
	GLfloat light_position[]={10, 10, 20.0f, 0.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
}
void setMaterial(){
	GLfloat	mat_ambient[]={0.7f, 0.7f, 0.7f, 1.0f};
	GLfloat	mat_diffuse[]={1.0f, 0.0f, 0.0f, 1.0f};
	GLfloat	mat_specular[]={1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat mat_shininess[] = {50.0f};

	glMaterialfv(GL_FRONT,GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT,GL_DIFFUSE, mat_diffuse);
}
void setCamera(){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(10, 6, 10, 0.0, 0.5, 0.0, 0.0, 1.0, 0.0);
}
void drawAxis(){
	float	xmax = 1.5, ymax = 1.5, zmax = 1.5;
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

	glRasterPos3f(1.5, 0, 0);
	glutBitmapCharacter(font, 'X');

	glRasterPos3f(0, 1.5, 0);
	glutBitmapCharacter(font, 'Y');

	glRasterPos3f(0, 0, 1.5);
	glutBitmapCharacter(font, 'Z');
}

void display(){
	glClearColor(1.0,1.0,1.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	setCamera();
	drawAxis();
	setLight();

	setMaterial();
	// Hình 1
	glPushMatrix();
	glTranslatef(1.0f, 0.0f, 0.0f);
	glutSolidTeapot(0.25);
	glPopMatrix();

	// Hình 2
	glDisable(GL_LIGHTING); 
    glColor3f(0.0f, 0.0f, 1.0f);
	glPushMatrix();
	glTranslatef(0.25f, 0.5f, 0.45f);
	glScalef(0.5f, 1.0f, 0.9f);
    glutWireCube(1.0);
    glPopMatrix();
    glEnable(GL_LIGHTING);

	glPushMatrix();
    glTranslatef(0.5f, 1.0f, 0.9f); 
    glutSolidTeapot(0.25);
    glPopMatrix();

	// Hình 3
	glPushMatrix();
    glTranslatef(0.0f, 0.0f, 1.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glutSolidTeapot(0.25); 
    glPopMatrix();

	// Hình 4
    glPushMatrix();
    glTranslatef(0.0f, 1.0f, 0.0f);
    glRotatef(60.0f, 0.0f, 1.0f, 0.0f);
    glScalef(0.5f, 0.5f, 0.5f);
    glutSolidTeapot(0.25);
    glPopMatrix();

	// Hình 5
	glPushMatrix();
	glTranslatef(1.0f, 0.0f, 0.0f);
	glutSolidTeapot(0.25);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.0f, 0.0f, 0.0f);
	glRotated(180.0f, 0.0f, 1.0f, 0.0f);
	glutSolidTeapot(0.25);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.0f, 0.0f, 1.0f);
	glRotated(-90.0f, 0.0f, 1.0f, 0.0f);
	glutSolidTeapot(0.25);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.0f, 0.0f, -1.0f);
	glRotated(90.0f, 0.0f, 1.0f, 0.0f);
	glutSolidTeapot(0.25);
	glPopMatrix();
	
	// Hình 6
	float cur_h = 0.0f;
	float cur_scale = 1.0f;
    const int numTeapots = 5;
    const float biggest_size = 0.25f;

    const float f_scale = 0.8f;
    const float d = 0.3f;

    for (int i = 0; i < numTeapots; ++i) {
        glPushMatrix();
        glTranslatef(0.0f, cur_h, 0.0f);
        glScalef(cur_scale, cur_scale, cur_scale);
        glutSolidTeapot(biggest_size); 
        glPopMatrix();
        cur_h += d;
        cur_scale *= f_scale;
    }

	// Hình 7
	const int numCubes = 5;
    const float distance = 0.3f;
    const float size = 0.2f;
    glColor3f(1.0f, 0.0f, 0.0f);

    for (int y = 0; y < numCubes; ++y) {
        for (int x = 0; x < numCubes - y; ++x) {
            for (int z = 0; z < numCubes - x - y; ++z) {
                if (y == 0 || z == 0) {
                    glPushMatrix();
                    glTranslatef(x * distance, y * distance, z * distance);
                    glutSolidCube(size);        
                    glPopMatrix();
                }
                
            }
        }
    }

	// Hình 8
	const int n = 4;
    const float size_base = 0.3f;
    float step = 0.3f;

    glPushMatrix();
    glutSolidCube(size_base);
    glPopMatrix();

    float scale = 0.8f;
    float pos = step;

    for (int i = 0; i < n; i++) {
        glPushMatrix();
        glTranslatef(pos, 0.0f, 0.0f);
        glRotatef(45.0f * (i + 1), 1.0f, 0.0f, 0.0f); 
        glScalef(scale, scale, scale);
        glutSolidCube(size_base);
        glPopMatrix();

        pos += step * scale; 
        scale *= 0.8f;
    }

    scale = 0.8f; 
    pos = step;  
    for (int i = 0; i < n; i++) {
        glPushMatrix();
        glTranslatef(0.0f, pos, 0.0f);
        glRotatef(45.0f * (i + 1), 0.0f, 1.0f, 0.0f);
        glScalef(scale, scale, scale);
        glutSolidCube(size_base);
        glPopMatrix();

        pos += step * scale;
        scale *= 0.8f;
    }

    scale = 0.8f; 
    pos = step;  
    for (int i = 0; i < n; i++) {
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, pos);
        glRotatef(45.0f * (i + 1), 0.0f, 0.0f, 1.0f);
        glScalef(scale, scale, scale);
        glutSolidCube(size_base);
        glPopMatrix();

        pos += step * scale;
        scale *= 0.8f;
    }

	glFlush();
}

int main(int argc, _TCHAR* argv[]){
	glutInit(&argc, (char**)argv); //initialize the tool kit
	glutInitDisplayMode(GLUT_SINGLE |GLUT_RGB |GLUT_DEPTH);
	glutInitWindowSize(screenWidth, screenHeight); //set window size
	glutInitWindowPosition(0, 0); // set window position on screen
	glutCreateWindow("Lab-Transformation"); // open the screen window

	glutDisplayFunc(display);

	init();
	glEnable(GL_DEPTH_TEST);

	glutMainLoop();
	return 0;
}

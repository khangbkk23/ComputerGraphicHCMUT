#include <Windows.h>
#include <math.h>
#include <iostream>
#include <GL/glut.h>
#include <tchar.h>
using namespace std;
/////////////////////////////////////////////////////////////////////
#define PI			3.1415926
#define	COLORNUM	14

float ColorArr[COLORNUM][3] = { { 1.0, 0.0, 0.0 },{ 0.0, 1.0, 0.0 },{ 0.0,  0.0, 1.0 },
					{ 1.0, 1.0,  0.0 },{ 1.0, 0.0, 1.0 },{ 0.0, 1.0, 1.0 },
					{ 0.3, 0.3, 0.3 },{ 0.5, 0.5, 0.5 },{ 0.9,  0.9, 0.9 },
					{ 1.0, 0.5,  0.5 },{ 0.5, 1.0, 0.5 },{ 0.5, 0.5, 1.0 },
					{ 0.0, 0.0, 0.0 },{ 0.7, 0.7, 0.7 } };
class Point3{
public:
	float x, y, z;
	void set(float dx, float dy, float dz) {
		x = dx; y = dy; z = dz;
	}
	void set(Point3& p) {
		x = p.x; y = p.y; z = p.z;
	}
	Point3() { x = y = z = 0; }
	Point3(float dx, float dy, float dz) {
		x = dx; y = dy; z = dz;
	}

};

class Vector3 {
public:
	float x, y, z;

	void set(float dx, float dy, float dz) {
		x = dx; y = dy; z = dz;
	}

	void set(Vector3& v) {
		x = v.x; y = v.y; z = v.z;
	}

	void flip() {
		x = -x; y = -y; z = -z;
	}

	void normalize();

	Vector3() {
		x = y = z = 0;
	}

	Vector3(float dx, float dy, float dz) {
		x = dx; y = dy; z = dz;
	}

	Vector3(Vector3& v) {
		x = v.x; y = v.y; z = v.z;
	}

	Vector3 cross(Vector3 b);

	float dot(Vector3 b);

};

class VertexID {
public:
	int	vertIndex;
	int	colorIndex;
};

class Face {
public:
	int	nVerts;
	VertexID* vert;

	Face() {
		nVerts = 0;
		vert = NULL;
	}
	~Face() {
		if (vert != NULL) {
			delete[] vert;
			vert = NULL;
		}
		nVerts = 0;
	}
};

class Mesh {
public:
	int	numVerts;
	Point3*	pt;

	int	numFaces;
	Face* face;
public:
	Mesh() {
		numVerts = 0;
		pt = NULL;
		numFaces = 0;
		face = NULL;
	}
	~Mesh() {
		if (pt != NULL)
			delete[] pt;

		if (face != NULL)
			delete[] face;
			
		numVerts = 0;
		numFaces = 0;
	}
	void DrawWireframe();
	void DrawColor();
	void DrawPoint();


	// void CreateCube(float fSize);
	// void CreateTetrahedron(float fSize);
	void CreateCuboid(float fSizeX, float fSizeY, float fSizeZ);
	void CreateCylinder(int nSegment, float fHeight, float fRadius);
	void CreateSphere(int nSlice, int nStack, float radius);
    void CreateTorus(int nSlice, int nStack, float R, float r);
	void CreateEightFacePlatonic(float fSize);
	void CreateTwentyFacePlatonic(float fSize);
	void CreateTwelveFacePlatonic(float fSize);
    void ClearMesh();
};

void Mesh::DrawWireframe() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for (int f = 0; f < numFaces; f++) {
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++) {
			int		iv = face[f].vert[v].vertIndex;

			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

void Mesh::DrawColor() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	for (int f = 0; f < numFaces; f++) {
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++) {
			int	iv = face[f].vert[v].vertIndex;
			int	ic = face[f].vert[v].colorIndex;

			ic = f % COLORNUM;

			glColor3f(ColorArr[ic][0], ColorArr[ic][1], ColorArr[ic][2]);
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}
void Mesh::DrawPoint() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	glPointSize(3);
	glColor3f(0, 0, 0);
	for (int f = 0; f < numVerts; f++) {
		glBegin(GL_POINTS);
		glVertex3f(pt[f].x, pt[f].y, pt[f].z);
		glEnd();
	}
}

// Clear mesh data
void Mesh::ClearMesh() {
    if (pt != nullptr) {
        delete[] pt;
        pt = nullptr;
    }
    if (face != nullptr) {
        for (int i = 0; i < numFaces; i++) {
            if (face[i].vert != nullptr) {
                delete[] face[i].vert;
                face[i].vert = nullptr;
            }
        }
        delete[] face;
        face = nullptr;
    }
    numVerts = 0;
    numFaces = 0;
}

// 1. Create Cuboid
void Mesh::CreateCuboid(float fSizeX, float fSizeY, float fSizeZ) {
    ClearMesh();

	numVerts = 8;
	pt = new Point3[numVerts];

	pt[0].set(-fSizeX, fSizeY, fSizeZ);
	pt[1].set(fSizeX, fSizeY, fSizeZ);
	pt[2].set(fSizeX, fSizeY, -fSizeZ);
	pt[3].set(-fSizeX, fSizeY, -fSizeZ);
	pt[4].set(-fSizeX, -fSizeY, fSizeZ);
	pt[5].set(fSizeX, -fSizeY, fSizeZ);
	pt[6].set(fSizeX, -fSizeY, -fSizeZ);
	pt[7].set(-fSizeX, -fSizeY, -fSizeZ);

	numFaces = 6;
	face = new Face[numFaces];

	//Left face
	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 5;
	face[0].vert[2].vertIndex = 6;
	face[0].vert[3].vertIndex = 2;

	//Right face
	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;
	face[1].vert[1].vertIndex = 3;
	face[1].vert[2].vertIndex = 7;
	face[1].vert[3].vertIndex = 4;

	//top face
	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 1;
	face[2].vert[2].vertIndex = 2;
	face[2].vert[3].vertIndex = 3;


	//bottom face
	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 7;
	face[3].vert[1].vertIndex = 6;
	face[3].vert[2].vertIndex = 5;
	face[3].vert[3].vertIndex = 4;

	//near face
	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 4;
	face[4].vert[1].vertIndex = 5;
	face[4].vert[2].vertIndex = 1;
	face[4].vert[3].vertIndex = 0;

	//Far face
	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 3;
	face[5].vert[1].vertIndex = 2;
	face[5].vert[2].vertIndex = 6;
	face[5].vert[3].vertIndex = 7;
}

// 2. Create Cylinder
void Mesh::CreateCylinder(int nSegment, float fHeight, float fRadius) {
    ClearMesh();

	numVerts = nSegment * 2 + 2;
	pt = new Point3[numVerts];
	float fAngle = 2.0 * PI / nSegment;
	float x, y, z;
	pt[0].set(0, fHeight/2.0, 0); // set diem 0
	for (int i = 0; i < nSegment; ++i) {
		x = fRadius * cos(fAngle * i);
		y = fHeight / 2.0;
		z = fRadius * sin(fAngle * i);
		pt[i + 1].set(x, y, z);
		y = -fHeight / 2.0;
		pt[i + 1 + nSegment].set(x, y, z); // set diem nguoc lai
	}
	pt[numVerts - 1].set(0, -fHeight/ 2.0, 0); // set diem cuoi cung

	numFaces= nSegment*3;
	face = new Face[numFaces];

	int idx = 0;
	for(int i = 0; i<nSegment; i++) {
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 0;
		if(i < nSegment -1)
			face[idx].vert[1].vertIndex = i + 2;
		else
			face[idx].vert[1].vertIndex = 1;
		face[idx].vert[2].vertIndex = i + 1;
		idx++;
	}

	for(int i = 0; i<nSegment; i++) {
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		
		face[idx].vert[0].vertIndex = i+1;
		if(i <nSegment - 1)
			face[idx].vert[1].vertIndex = i+2;
		else
			face[idx].vert[1].vertIndex = 1;
		face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + nSegment;
		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + nSegment;

		idx++;
	}

	for (int i = 0; i<nSegment; i++) {
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = numVerts - 1;
		if(i < nSegment -1)
			face[idx].vert[2].vertIndex = i + 2 + nSegment;
		else
			face[idx].vert[2].vertIndex = 1 + nSegment;
		face[idx].vert[1].vertIndex = i + 1 + nSegment;
		idx++;
	}
}

// 3. Create Sphere
void Mesh::CreateSphere(int nSlice, int nStack, float radius) {
    ClearMesh();

    numVerts = (nStack + 1) * nSlice;
    pt = new Point3[numVerts];

    float stackAngle, sliceAngle;
    int idx = 0;

    for (int i = 0; i <= nStack; i++) {
        stackAngle = PI / 2 - i * PI / nStack; 
        float xy = radius * cos(stackAngle);
        float z = radius * sin(stackAngle);

        for (int j = 0; j < nSlice; j++) {
            sliceAngle = j * 2 * PI / nSlice;

            float x = xy * cos(sliceAngle);
            float y = xy * sin(sliceAngle);

            pt[idx++].set(x, y, z);
        }
    }

    numFaces = nSlice * nStack;
    face = new Face[numFaces];
    idx = 0;

    for (int i = 0; i < nStack; i++) {
        for (int j = 0; j < nSlice; j++) {

            int first = i * nSlice + j;
            int second = first + nSlice;

            int next = (j + 1) % nSlice;

            face[idx].nVerts = 4;
            face[idx].vert = new VertexID[4];

            face[idx].vert[0].vertIndex = first;
            face[idx].vert[1].vertIndex = i * nSlice + next;
            face[idx].vert[2].vertIndex = (i + 1) * nSlice + next;
            face[idx].vert[3].vertIndex = second;

            idx++;
        }
    }
}

// 4. Create Torus
void Mesh::CreateTorus(int nSlice, int nStack, float R, float r) {
    ClearMesh();
    
    numVerts = (nStack + 1) * (nSlice + 1);
    pt = new Point3[numVerts];
    
    for (int i = 0; i <= nStack; i++) {
        float phi = (float)i * 2.0f * PI / nStack;
        for (int j = 0; j <= nSlice; j++) {
            float theta = (float)j * 2.0f * PI / nSlice;
            float x = (R + r * cos(theta)) * cos(phi);
            float y = (R + r * cos(theta)) * sin(phi);
            float z = r * sin(theta);
            pt[i * (nSlice + 1) + j].set(x, y, z);
        }
    }

    numFaces = nStack * nSlice;
    face = new Face[numFaces];
    int f = 0;
    for (int i = 0; i < nStack; i++) {
        for (int j = 0; j < nSlice; j++) {
            face[f].nVerts = 4;
            face[f].vert = new VertexID[4];
            face[f].vert[0].vertIndex = i * (nSlice + 1) + j;
            face[f].vert[1].vertIndex = (i + 1) * (nSlice + 1) + j;
            face[f].vert[2].vertIndex = (i + 1) * (nSlice + 1) + (j + 1);
            face[f].vert[3].vertIndex = i * (nSlice + 1) + (j + 1);
            f++;
        }
    }
}

// 5. Create Eight-Face Platonic
void Mesh::CreateEightFacePlatonic(float fSize) {
	ClearMesh();
	numVerts = 6;
	pt = new Point3[numVerts];

	pt[0].set(0, fSize, 0); // (+Y)
	pt[1].set(-fSize, 0, 0); // (-X)
	pt[2].set(0, 0, fSize); // (+Z)
	pt[3].set(fSize, 0, 0); // (+X)
	pt[4].set(0, 0, -fSize); // (-Z)
	pt[5].set(0, -fSize, 0); // (-Y)

	numFaces = 8;
	face = new Face[numFaces];
	
	int faceIndices[8][3] = {
        {0, 1, 2}, {0, 2, 3}, {0, 3, 4}, {0, 4, 1},
        {5, 2, 1}, {5, 3, 2}, {5, 4, 3}, {5, 1, 4}
    };

	for (int i = 0; i < numFaces; ++i) {
		face[i].nVerts = 3;
		face[i].vert = new VertexID[3];

		float nx = 0.0f, ny = 0.0f, nz = 0.0f;

        for (int j = 0; j < 3; j++) {
            int vIdx = faceIndices[i][j];
            face[i].vert[j].vertIndex = vIdx;
            
            nx += pt[vIdx].x;
            ny += pt[vIdx].y;
            nz += pt[vIdx].z;
        }
	}
}

// 6. Create Twenty-Face Platonic
void Mesh::CreateTwentyFacePlatonic(float fSize) {
	ClearMesh();
	float tau = (sqrt(5.0f) - 1.0f) / 2.0f;

	numVerts = 12;
	pt = new Point3[numVerts];
	pt[0].set(0, fSize, fSize*tau);
	pt[1].set(0, fSize, -fSize*tau);
	pt[2].set(fSize, fSize*tau, 0);
	pt[3].set(fSize, -fSize*tau, 0);
	pt[4].set(0, -fSize, -fSize*tau);
	pt[5].set(0, -fSize, fSize*tau);
	pt[6].set(fSize*tau, 0, fSize);
	pt[7].set(-fSize*tau, 0, fSize);
	pt[8].set(fSize*tau, 0, -fSize);
	pt[9].set(-fSize*tau, 0, -fSize);
	pt[10].set(-fSize, fSize*tau, 0);
	pt[11].set(-fSize, -fSize*tau, 0);

	numFaces = 20;
	face = new Face[numFaces];
	int faceIndices[20][3] = {
		{0,6,2},
		{6,3,2},
		{6,5,3},
		{7,5,6},
		{7,6,0},
		{2,3,8},
		{1,2,8},
		{0,2,1},
		{10,0,1},
		{10,1,9},
		{1,8,9},
		{3,4,8},
		{5,4,3},
		{11,4,5},
		{11,7,10},
		{7,0,10},
		{9,4,11},
		{9,8,4},
		{11,5,7},
		{11,10,9}
	};
	for (int i = 0; i < numFaces; ++i) {
		face[i].nVerts = 3;
		face[i].vert = new VertexID[3];
		for (int j = 0; j < 3; ++j) {
			face[i].vert[j].vertIndex = faceIndices[i][j];
		}
	}
}

//////////////////////////////////////////////////////////////////////
int	screenWidth = 1000;
int	screenHeight = 500;

float angle = 0;

int	nChoice = 0;

// Create mesh objects
Mesh cuboid;
Mesh cylinder;
Mesh sphere;
Mesh torus;
Mesh eightFacePlatonic;
Mesh twentyFacePlatonic;
Mesh twelveFacePlatonic;

void drawAxis() {
	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
		glColor3f(1, 0, 0);
		glVertex3f(0, 0, 0);//x - red
		glVertex3f(6, 0, 0);

		glColor3f(0, 1, 0);
		glVertex3f(0, 0, 0);//y - green
		glVertex3f(0, 6, 0);

		glColor3f(0, 0, 1);
		glVertex3f(0, 0, 0);//z - blue
		glVertex3f(0, 0, 6);
	glEnd();
}
void myDisplay() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(4.5, 4, 4, 0, 0, 0, 0, 1, 0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	////////////////////////////////////////////////////
	glViewport(0, 0, screenWidth / 2, screenHeight);

	glPushMatrix();
	drawAxis();

	glRotatef(angle, 0, 1, 0);

	glColor3f(0, 0, 0);
	if (nChoice == 1)
		cuboid.DrawWireframe();
	else if (nChoice == 2)
		cylinder.DrawWireframe();
    else if (nChoice == 3)
        sphere.DrawWireframe();
    else if (nChoice == 4)
        torus.DrawWireframe();
	else if (nChoice == 5)
		eightFacePlatonic.DrawWireframe();
	else if (nChoice == 6)
		twentyFacePlatonic.DrawWireframe();
	else if (nChoice == 7)
		twelveFacePlatonic.DrawWireframe();
	else if (nChoice == 8)
		cuboid.DrawPoint();


	/////////////////////////////////////////////////////////////
	glViewport(screenWidth / 2, 0, screenWidth / 2, screenHeight);

	glPopMatrix();
	drawAxis();
	glRotatef(angle, 0, 1, 0);

	if (nChoice == 1)
		cuboid.DrawColor();
	else if (nChoice == 2)
		cylinder.DrawColor();
    else if (nChoice == 3)
        sphere.DrawColor();
    else if (nChoice == 4)
        torus.DrawColor();
	else if (nChoice == 5)
		eightFacePlatonic.DrawColor();
	else if (nChoice == 6)
		twentyFacePlatonic.DrawColor();
	else if (nChoice == 7)
		twelveFacePlatonic.DrawColor();
	else if (nChoice == 8)
		cuboid.DrawPoint();

	glFlush();
	glutSwapBuffers();
}
void mySpecialFunc(int key, int x, int y) {
	if (key == GLUT_KEY_LEFT)
		angle = angle + 5;
	else if (key == GLUT_KEY_RIGHT)
		angle = angle - 5;
	glutPostRedisplay();
}
void myKeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case '1':
		nChoice = 1;
		break;
	case '2':
		nChoice = 2;
		break;
	case '3':
		nChoice = 3;
		break;
	case '4':
		nChoice = 4;
		break;
	case '5':
		nChoice = 5;
		break;
	case '6':
		nChoice = 6;
		break;
	case '7':
		nChoice = 7;
		break;
	case '8':
		nChoice = 8;
		break;
	}
	glutPostRedisplay();
}
void myInit() {
	float fHalfSize = 5;

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-fHalfSize, fHalfSize, -fHalfSize, fHalfSize, -1000, 1000);
}


int main(int argc, _TCHAR* argv[]) {
	cout << "Press -> or <- to rotate" << endl;

	cout << "1. Cuboid" << endl;
	cout << "2. Cylinder" << endl;
	cout << "3. Sphere" << endl;
	cout << "4. Torus" << endl;
	cout << "5. Eight-Face Platonic" << endl;
	cout << "6. Twenty-Face Platonic" << endl;
	cout << "7. Twelve-Face Platonic" << endl;
	cout << "8. Cuboid (Point mode)" << endl;

	cout << endl<< "Input the choice: " << endl;
	cin  >> nChoice;

	glutInit(&argc, (char**)argv); //initialize the tool kit
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);//set the display mode
	glutInitWindowSize(screenWidth, screenHeight); //set window size
	glutInitWindowPosition(100, 100); // set window position on screen
	glutCreateWindow("Lab 2-Mesh"); // open the screen window

	myInit();
	glutKeyboardFunc(myKeyboard);
	glutDisplayFunc(myDisplay);
	glutSpecialFunc(mySpecialFunc);

	cuboid.CreateCuboid(4.0f, 1.5f, 2.0f);
	cylinder.CreateCylinder(100, 4.0f, 2.0f);
    sphere.CreateSphere(80, 80, 2.0f);
    torus.CreateTorus(10, 40, 3.0f, 1.0f);
	eightFacePlatonic.CreateEightFacePlatonic(2.0f);
	twentyFacePlatonic.CreateTwentyFacePlatonic(2.0f);

	glutMainLoop();
    	return 0;
}
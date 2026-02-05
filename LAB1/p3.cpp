#include "windows.h"
#include "GL/glut.h"
#include "math.h"

#define PI 3.14159265358979323846

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // Nền trắng
    glColor3f(1.0, 0.0, 0.0);         // Nét vẽ đỏ
    glLineWidth(2.0);                 // Tăng độ dày nét vẽ để dễ quan sát

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-75.0, 75.0, -75.0, 75.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void display() {
    float R = 50.0;
    float x0 = 0.0;
    float y0 = 0.0;

    glClear(GL_COLOR_BUFFER_BIT);

    // BƯỚC 1: Vẽ các đường nối từ tâm ra biên (Các cạnh bên của tam giác)
    // Sử dụng GL_LINES: Cứ 2 đỉnh tạo thành một đoạn thẳng rời rạc
    glBegin(GL_LINES);
    for (int a = 0; a < 360; a += 10) {
        float rad = a * PI / 180.0;
        float x = x0 + R * cos(rad);
        float y = y0 + R * sin(rad);

        // Định nghĩa đoạn thẳng từ Tâm -> Đỉnh biên
        glVertex2f(x0, y0); // Đỉnh 1: Tâm
        glVertex2f(x, y);   // Đỉnh 2: Điểm trên đường tròn
    }
    glEnd();

    // BƯỚC 2: Vẽ đường viền tròn (Các cạnh đáy của tam giác)
    // Sử dụng GL_LINE_LOOP như câu 2 để nối kín các đỉnh biên
    glBegin(GL_LINE_LOOP);
    for (int a = 0; a < 360; a += 10) {
        float rad = a * PI / 180.0;
        float x = x0 + R * cos(rad);
        float y = y0 + R * sin(rad);
        
        glVertex2f(x, y);
    }
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Problem 3: Circle divided into Triangles");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
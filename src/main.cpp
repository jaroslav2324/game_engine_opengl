#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

#include "triangulation/structures.h"

#define WIN_WIDTH 1000
#define WIN_HEIGHT 800


void displayMe(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f); // Красный цвет
    glVertex2d(0.2f, 0.3f);
    glVertex2d(0.2f, 0.6f);
    glVertex2d(0.6f, 0.6f);
    glEnd();
    glFlush();
}


int main(int argc, char** argv) {

    Node n1(100, 200);
    Node n2(100, 400);
    Node n3(300, 400);

    NodesEdgesTriangles(n1, n2, n3);

    // Пример использования
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Hello world!");
    glOrtho(-1, 1, -1, 1, -1, 1); // Установка ортографической проекции
    glutDisplayFunc(displayMe);
    glutMainLoop();
    return 0;
}
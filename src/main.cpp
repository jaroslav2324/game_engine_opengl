#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

#include "rendering/Renderer.h"
#include "utils/randomGeneration.h"

#define WIN_WIDTH 1000
#define WIN_HEIGHT 800

#define RANDOM_TRIANG_POINTS_TEST true

Renderer renderer(WIN_WIDTH, WIN_HEIGHT);


void displayMe(void) {
    // std::cout << "display" << std::endl;
    // auto points = generateRandomPoints(100, Point2D(500, 400), -450, 450, -350, 350);
    // auto triangles = triangulateBowyerWatson(points);
    // renderer.renderTriangles(triangles);
    renderer.render();
}

void myIdleFunc(){

}

void mouseClick(int button, int state, int x, int y) {

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        std::cout << "left mouse butoon pressed" << std::endl;

        glutPostRedisplay();
    }
}


int main(int argc, char** argv) {

    Circle cir1(&renderer, Point2D(200, 200), 100);
    Circle cir2(&renderer, Point2D(600, 600), 200);

    ColorRGB color;
    cir1.setCircleColor(color(1.0f, 0.0f, 0.0f));
    cir2.setCircleColor(color(0.0f, 1.0f, 0.0f));

    renderer.addCircleToPtrs(&cir1);
    renderer.addCircleToPtrs(&cir2);

    // Пример использования
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("");
    glutDisplayFunc(displayMe);
    glutIdleFunc(myIdleFunc);
    glutMouseFunc(mouseClick);
    glutMainLoop();

    return 0;
}
#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

#include "rendering/Renderer.h"
#include "utils/randomGeneration.h"
#include "physics/CollisionManager.h"

#define WIN_WIDTH 1000
#define WIN_HEIGHT 800

#define RANDOM_TRIANG_POINTS_TEST true

Renderer renderer(WIN_WIDTH, WIN_HEIGHT);

Circle cir1(Point2D(200, 200), 100);
Circle cir2(Point2D(600, 600), 200);


void displayMe(void) {
    // std::cout << "display" << std::endl;
    // auto points = generateRandomPoints(100, Point2D(500, 400), -450, 450, -350, 350);
    // auto triangles = triangulateBowyerWatson(points);
    // renderer.renderTriangles(triangles);
    renderer.render();
    glutSwapBuffers();
}

void myIdleFunc(){

}

void mouseClick(int button, int state, int x, int y) {

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        std::cout << "left mouse butoon pressed" << std::endl;

        glutPostRedisplay();
    }
}

void timerCallback60sec(int value){

    cir1.applyPhysics(1.0f/60) ;
    cir2.applyPhysics(1.0f/60) ;


    glutTimerFunc(1.0f/60, timerCallback60sec, 123);
}

void timerCallback30sec(int value){

    glutPostRedisplay();
    glutTimerFunc(1.0f/30, timerCallback30sec, 123);
}


int main(int argc, char** argv) {

    CollisionManager collisionManager;

    // std::cout << collisionManager.checkCircleCircleIntersection(cir1, cir2) << std::endl;

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
    glutTimerFunc(0, timerCallback60sec, 123);
    glutTimerFunc(0, timerCallback30sec, 123);
    glutMouseFunc(mouseClick);
    glutMainLoop();

    return 0;
}
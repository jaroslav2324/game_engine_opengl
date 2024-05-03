#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

#include "rendering/Renderer.h"
#include "physics/CollisionManager.h"
#include "physics/PhysicsManager.h"
#include "objects/ObjectManager.h"

#define WIN_WIDTH 1000
#define WIN_HEIGHT 800

Renderer renderer(WIN_WIDTH, WIN_HEIGHT);
PhysicsManager physicsManager;
CollisionManager collisionManager;

void displayMe(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    renderer.render();
    glFinish();
    glutSwapBuffers();
}

void myIdleFunc(){

}

void mouseClick(int button, int state, int x, int y) {

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        std::cout << "left mouse butoon pressed" << std::endl;

        //glutPostRedisplay();
    }
}

// void timerCallback60sec(int value){

//     cir1.applyPhysics(1.0f/60) ;
//     cir2.applyPhysics(1.0f/60) ;
//     rect1.applyPhysics(1.0f/60) ;


//     glutTimerFunc(1.0f/60, timerCallback60sec, 123);
// }

void timerCallback60sec(int value){

    physicsManager.updatePhysics(1.0f / 60);
    collisionManager.resolveCollisions();
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, timerCallback60sec, 123);
}



int main(int argc, char** argv) {

    ColorRGB color;

    ObjectManager objManager(&renderer, &collisionManager, &physicsManager);

    Rect* borderRect1 = objManager.createRect(Point2D(0, 400), 50, 900);
    borderRect1->setStatic(true);
    Rect* borderRect2 = objManager.createRect(Point2D(500, 0), 1100, 50);
    borderRect2->setStatic(true);
    Rect* borderRect3 = objManager.createRect(Point2D(1000, 400), 50, 900);
    borderRect3->setStatic(true);
    Rect* borderRect4 = objManager.createRect(Point2D(500, 800), 1100, 50);
    borderRect4->setStatic(true);

    Circle* cir1 = objManager.createCircle(Point2D(450, 200), 100);
    cir1->setCircleColor(color(1.0f, 0.0f, 0.0f));
    cir1->setGravityScale(5);
    cir1->setRenderEdges(true);

    Circle* cir2 = objManager.createCircle(Point2D(600, 600), 150);
    cir2->setCircleColor(color(0.0f, 1.0f, 0.0f));
    cir2->setGravityScale(-2);
    cir2->setMass(100);
    cir2->setStatic(true);

    // Rect* rect1 = objManager.createRect(Point2D(400, 200), 200, 100);
    // rect1->setRectColor(color(0.0f, 0.0f, 1.0f));


    // Пример использования
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("");
    glutDisplayFunc(displayMe);
    glutIdleFunc(myIdleFunc);
    
    // glutTimerFunc(0, timerCallback60sec, 123);
    glutTimerFunc(1000 / 60, timerCallback60sec, 123);
    glutMouseFunc(mouseClick);
    glutMainLoop();

    std::cout << "Exiting..." << std::endl;
    objManager.~ObjectManager();

    return 0;
}
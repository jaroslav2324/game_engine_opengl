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

void mouseClick(int button, int state, int x, int y) {

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        std::cout << "left mouse butoon pressed" << std::endl;

        //glutPostRedisplay();
    }
}

int cps = 0;

void timerCallback60sec(int value){

    physicsManager.updatePhysics(1.0f / 60);
    collisionManager.resolveCollisions();
    cps++;
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, timerCallback60sec, 123);
}

// collosion checks per sec
void cpsChecker(int value){
    std::cout << "CPS: " << cps << std::endl;
    cps = 0;
    glutTimerFunc(1000, cpsChecker, 123);
}

void loadBasicScene(ObjectManager& objManager){
    Rect* borderRect1 = objManager.createRect(Point2D(0, 400), 50, 900);
    borderRect1->setStatic(true);
    Rect* borderRect2 = objManager.createRect(Point2D(500, 0), 1100, 50);
    borderRect2->setStatic(true);
    Rect* borderRect3 = objManager.createRect(Point2D(1000, 400), 50, 900);
    borderRect3->setStatic(true);
    Rect* borderRect4 = objManager.createRect(Point2D(500, 800), 1100, 50);
    borderRect4->setStatic(true);

    Circle* cir1 = objManager.createCircle(Point2D(450, 200), 100);
    cir1->setCircleColor({1.0f, 0.0f, 0.0f});
    cir1->setGravityScale(0);
    // cir1->setStatic(true);
    // cir1->setVelocity(Vector2D(550, 50));
    cir1->setRenderEdges(true);
    cir1->setElastic(0.8);
    cir1->setMass(1000);

    // Circle* cir2 = objManager.createCircle(Point2D(600, 600), 100);
    // cir2->setCircleColor({0.0f, 0.7f, 0.0f});
    // cir2->setGravityScale(0);
    // cir2->setVelocity(Vector2D(-600, -300));
    // cir2->setMass(100);
    // cir2->setRenderEdges(true);


    Circle* cir3 = objManager.createCircle(Point2D(800, 200), 100);
    cir3->setCircleColor({0.0f, 1.0f, 1.0f});
    cir3->setVelocity(Vector2D(550, 50));
    cir3->setGravityScale(0);
    cir3->setRenderEdges(true);

    // Circle* cir4 = objManager.createCircle(Point2D(300, 400), 100);
    // cir4->setCircleColor({0.0f, 0.0f, 0.7f});
    // cir4->setGravityScale(0);
    // cir4->setRenderEdges(true);
}

void loadPingPong(ObjectManager& objManager){
    Rect* borderRect1 = objManager.createRect(Point2D(0, 400), 50, 900);
    borderRect1->setStatic(true);
    Rect* borderRect2 = objManager.createRect(Point2D(500, 0), 1100, 50);
    borderRect2->setStatic(true);
    Rect* borderRect3 = objManager.createRect(Point2D(1000, 400), 50, 900);
    borderRect3->setStatic(true);
    Rect* borderRect4 = objManager.createRect(Point2D(500, 800), 1100, 50);
    borderRect4->setStatic(true);

    Rect* rocketLeft = objManager.createRect(Point2D(100, 400), 30, 200);
    rocketLeft->setStatic(true);
    Rect* rocketRight = objManager.createRect(Point2D(900, 400), 30, 200);
    rocketRight->setStatic(true);

    Circle* ball = objManager.createCircle(Point2D(500, 400), 30);
    ball->setCircleColor({0.8f, 0.8f, 0.8f});
    ball->setGravityScale(0);
    srand(time(0));
    float velDir = rand() % 2;
    float x = (velDir == 0) ? -500 : 500;
    ball->setVelocity(Point2D(x, 0));
}


int main(int argc, char** argv) {

    ColorRGB color;

    ObjectManager objManager(&renderer, &collisionManager, &physicsManager);
    loadBasicScene(objManager);
    // loadPingPong(objManager);

    // Пример использования
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Collision engine");
    glutDisplayFunc(displayMe);
    
    // glutTimerFunc(0, timerCallback60sec, 123);
    glutTimerFunc(1000 / 60, timerCallback60sec, 123);
    glutTimerFunc(1000, cpsChecker, 123);
    glutMouseFunc(mouseClick);
    glutMainLoop();

    std::cout << "Exiting..." << std::endl;
    objManager.~ObjectManager();

    return 0;
}
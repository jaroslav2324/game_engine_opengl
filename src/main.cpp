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
#include "scenes/Scenes.h"

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
    // std::cout << "CPS: " << cps << std::endl;
    cps = 0;
    glutTimerFunc(1000, cpsChecker, 123);
}

int main(int argc, char** argv) {

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Collision engine");
    glutDisplayFunc(displayMe);

    ObjectManager objManager(&renderer, &collisionManager, &physicsManager);
    // loadBasicScene(objManager);
    // loadPingPong(objManager);
    loadTestRectsScene(objManager);

    // Пример использования
    
    // glutTimerFunc(0, timerCallback60sec, 123);
    glutTimerFunc(1000 / 60, timerCallback60sec, 123);
    glutTimerFunc(1000, cpsChecker, 123);
    glutMouseFunc(mouseClick);
    glutMainLoop();

    std::cout << "Exiting..." << std::endl;
    objManager.~ObjectManager();

    return 0;
}
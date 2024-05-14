#include "Scenes.h"

bool leftMouseBtnJustPressed = false;
bool pointCaptured = false;
SoftbodyPoint* point = nullptr;

int mouseX, mouseY;

ObjectManager* localPtrToObjManager = nullptr;

void mouseClickSoftbodyScene(int button, int state, int x, int y) {

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        std::cout << "left mouse button pressed" << std::endl;
        leftMouseBtnJustPressed = true;
        mouseX = x;
        mouseY = y;
    }
    else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        std::cout << "left mouse button released" << std::endl;
        leftMouseBtnJustPressed = false;
        pointCaptured = false;
        point = nullptr;
    }
}

void mouseMoveSoftbodyScene(int x, int y){
    mouseX = x;
    mouseY = y;
}

void mouseCaptureCallback(int value){

    if (leftMouseBtnJustPressed){
        point = localPtrToObjManager->getSoftbodyPointContaining(Point2D(mouseX, mouseY));
        if (point != nullptr){
            pointCaptured = true;
        }

        leftMouseBtnJustPressed = false;
    }
    if (pointCaptured){
        point->setPosition(Point2D(mouseX, mouseY));
    }

    glutTimerFunc(1000.0f / 60.0f, mouseCaptureCallback, 123);
}


void loadSoftbodyScene(ObjectManager &objManager){
    localPtrToObjManager = &objManager;

    loadBorders(objManager);
    Softbody* rect = objManager.createSoftRect({300, 500}, 40, 80);
    rect->setGravityScale(0.1f);

    Softbody* circle = objManager.createSoftCircle({700, 300}, 50, 8);
    circle->setGravityScale(1.0f);
    circle->addVelocity({-200, 50});

    Softbody* circle2 = objManager.createSoftCircle({500, 300}, 50, 8);
    circle2->setGravityScale(0.0f);
    circle2->setStiffness(20.0f);

    // Softbody* circle3 = objManager.createSoftCircle({300, 300}, 50, 8);
    // circle3->setGravityScale(1.0f);
    // circle3->setStiffness(5.0f);

    glutMouseFunc(mouseClickSoftbodyScene);
    glutMotionFunc(mouseMoveSoftbodyScene);
    glutTimerFunc(0, mouseCaptureCallback, 123);
}
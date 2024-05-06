#include "Scenes.h"

Rect* pingPongLeftRocket = nullptr;
Rect* pingPongRightRocket = nullptr;
Circle* ball = nullptr;

bool wPressed = false;
bool sPressed = false;
bool arrUpPressed = false;
bool arrDownPressed = false;

unsigned int startDelaySecs = 3;

int upRocketBorder = 50;
int downRocketBorder = 750;

int rocketSpeed = 400;
int startBallSpeed = 500;
int ballSpeed = 500;
int deltaSpeedOnEachHit = 20;

void pingPongHandleKeyPress(unsigned char key, int x, int y) {
    // std::cout << "Ping pong keyboard pressed" << std::endl;
    // Handle the key press event
    switch (key) {
    case 'w':
        wPressed = true;
        break;
    case 's':
        sPressed = true;
        break;
    }
}

void pingPongHandleSpecialKeyPress(int key, int x, int y){
    // std::cout << "Ping pong special keyboard pressed" << std::endl;
    switch (key) {
    case GLUT_KEY_UP:
        arrUpPressed = true;
        break;
    case GLUT_KEY_DOWN:
        arrDownPressed = true;
        break;
    }
}

void pingPongHandleKeyRelease(unsigned char key, int x, int y){
    // std::cout << "Ping pong keyboard released" << std::endl;
    switch (key)    {
    case 'w':
        wPressed = false;
        break;
    case 's':
        sPressed = false;
        break;
    }
}

void pingPongHandleSpecialKeyRelease(int key, int x, int y){
    // std::cout << "Ping pong special keyboard released" << std::endl;
    switch (key) {
    case GLUT_KEY_UP:
        arrUpPressed = false;
        break;
    case GLUT_KEY_DOWN:
        arrDownPressed = false;
        break;
    }
}

void rocketMovingHandleTimer(int value){
    float deltaTimeS = (1000.0f / 60) / 1000;
    if (wPressed){
        Vector2D leftPos = pingPongLeftRocket->getCenter();
        float h = pingPongLeftRocket->getHeight();
        if (leftPos.y - h / 2 > upRocketBorder){
            pingPongLeftRocket->setCenter(Point2D(leftPos.x, leftPos.y - deltaTimeS * rocketSpeed));
        }
    }
    if (sPressed){
        Vector2D leftPos = pingPongLeftRocket->getCenter();
        float h = pingPongLeftRocket->getHeight();
        if (leftPos.y + h / 2 < downRocketBorder){
            pingPongLeftRocket->setCenter(Point2D(leftPos.x, leftPos.y + deltaTimeS * rocketSpeed));
        }
    }
    if (arrUpPressed){
        Vector2D rightPos = pingPongRightRocket->getCenter();
        float h = pingPongRightRocket->getHeight();
        if (rightPos.y - h / 2 > upRocketBorder){
            pingPongRightRocket->setCenter(Point2D(rightPos.x, rightPos.y - deltaTimeS * rocketSpeed));
        }
    }
    if (arrDownPressed){
        Vector2D rightPos = pingPongRightRocket->getCenter();
        float h = pingPongRightRocket->getHeight();
        if (rightPos.y + h / 2 < downRocketBorder){
            pingPongRightRocket->setCenter(Point2D(rightPos.x, rightPos.y + deltaTimeS * rocketSpeed));
        }
    }
    glutTimerFunc(1000 / 60, rocketMovingHandleTimer, 123);
}

void startGameCallback(int value){
    // set random velocity direction
    // float xDir = randomFloat(-1, 1);
    // float yDir = randomFloat(-0.7, 0.7);
    // Vector2D direction(xDir, yDir);
    // direction = direction.normalize();
    // direction *= ballSpeed;
    // ball->setVelocity(direction);
    Vector2D testVel(-500, 100);
    ball->setVelocity(testVel);
}

void startGame(){
    ballSpeed = 500;
    ball->setCenter(Point2D(500, 400));
    ball->setVelocity({0, 0});
    pingPongLeftRocket->setCenter({100, 400});
    pingPongRightRocket->setCenter({900, 400});
    glutTimerFunc(startDelaySecs * 1000, startGameCallback, 123);
}

void loadPingPong(ObjectManager& objManager){
    Rect* borderRect1 = objManager.createRect(Point2D(0, 400), 50, 900);
    borderRect1->setStatic(true);
    borderRect1->setRectColor({0.3f, 0.0f, 0.0f});
    borderRect1->setOnCollisionCallback([](){
        startGame();
        });

    Rect* borderRect2 = objManager.createRect(Point2D(500, 0), 1100, 50);
    borderRect2->setStatic(true);

    Rect* borderRect3 = objManager.createRect(Point2D(1000, 400), 50, 900);
    borderRect3->setStatic(true);
    borderRect3->setRectColor({0.3f, 0.0f, 0.0f});
    borderRect3->setOnCollisionCallback([](){
        startGame();
        });

    Rect* borderRect4 = objManager.createRect(Point2D(500, 800), 1100, 50);
    borderRect4->setStatic(true);

    pingPongLeftRocket = objManager.createRect(Point2D(100, 400), 30, 200);
    pingPongLeftRocket->setRectColor({1.0f, 1.0f, 1.0f});
    pingPongLeftRocket->setStatic(true);
    pingPongLeftRocket->setOnCollisionCallback([](){    
        ballSpeed += deltaSpeedOnEachHit;
        Vector2D currVel = ball->getVelocity();
        Vector2D newVel  = currVel * ballSpeed / (ballSpeed - deltaSpeedOnEachHit);
        ball->setVelocity(newVel);
    });

    pingPongRightRocket = objManager.createRect(Point2D(900, 400), 30, 200);
    pingPongRightRocket->setRectColor({1.0f, 1.0f, 1.0f});
    pingPongRightRocket->setStatic(true);
    pingPongRightRocket->setOnCollisionCallback([](){    
        ballSpeed += deltaSpeedOnEachHit;
        Vector2D currVel = ball->getVelocity();
        Vector2D newVel  = currVel * ballSpeed / (ballSpeed - deltaSpeedOnEachHit);
        ball->setVelocity(newVel);
    });

    ball = objManager.createCircle(Point2D(500, 400), 30);
    ball->setCircleColor({0.0f, 1.0f, 1.0f});
    ball->setGravityScale(0);

    srand(time(0));

    glutKeyboardFunc(pingPongHandleKeyPress);
    glutSpecialFunc(pingPongHandleSpecialKeyPress);
    glutKeyboardUpFunc(pingPongHandleKeyRelease);
    glutSpecialUpFunc(pingPongHandleSpecialKeyRelease);

    glutTimerFunc(0, rocketMovingHandleTimer, 123);
    startGame();
}
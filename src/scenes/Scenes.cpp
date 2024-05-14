#include "Scenes.h"


void loadBasicScene(ObjectManager& objManager){

    loadBorders(objManager);

    Circle* cir1 = objManager.createCircle(Point2D(450, 200), 100);
    cir1->setCircleColor({1.0f, 0.0f, 0.0f});
    cir1->setGravityScale(0);
    // cir1->setStatic(true);
    // cir1->setVelocity(Vector2D(550, 50));
    cir1->setRenderEdges(true);
    cir1->setElastic(0.8);
    cir1->setMass(1000);

    Circle* cir2 = objManager.createCircle(Point2D(600, 600), 50);
    cir2->setCircleColor({0.0f, 0.7f, 0.0f});
    cir2->setGravityScale(0);
    cir2->setVelocity(Vector2D(-600, -300));
    cir2->setMass(100);
    cir2->setRenderEdges(true);

    Circle* cir3 = objManager.createCircle(Point2D(800, 200), 50);
    cir3->setCircleColor({0.0f, 1.0f, 1.0f});
    cir3->setVelocity(Vector2D(550, 50));
    cir3->setGravityScale(0);
    cir3->setRenderEdges(true);

    Circle* cir4 = objManager.createCircle(Point2D(300, 400), 50);
    cir4->setCircleColor({0.0f, 0.0f, 0.7f});
    cir4->setGravityScale(0);
    cir4->setRenderEdges(true);
}

void loadTestRectsScene(ObjectManager &objManager){
    loadBorders(objManager);

    Rect* rect1 = objManager.createRect({200, 200}, 200, 100);
    rect1->setGravityScale(0);
    rect1->setVelocity({300, 50});

    Rect* rect2 = objManager.createRect({600, 150}, 150, 100);
    rect2->setGravityScale(0);
    rect2->setStatic(true);

    Rect* rect3 = objManager.createRect({600, 600}, 100, 200);
    rect3->setGravityScale(0);
}

void loadBorders(ObjectManager &objManager){
    Rect* borderRect1 = objManager.createRect(Point2D(-50, 400), 120, 900);
    borderRect1->setStatic(true);
    Rect* borderRect2 = objManager.createRect(Point2D(500, -50), 1100, 120);
    borderRect2->setStatic(true);
    Rect* borderRect3 = objManager.createRect(Point2D(1050, 400), 120, 900);
    borderRect3->setStatic(true);
    Rect* borderRect4 = objManager.createRect(Point2D(500, 850), 1100, 120);
    borderRect4->setStatic(true);
}


#include "ObjectManager.h"

ObjectManager::ObjectManager(Renderer *renderer, CollisionManager *collisionManager, PhysicsManager *physicsManager){
    this->renderer = renderer;
    this->collisionManager = collisionManager;
    this->physicsManager = physicsManager;
}

ObjectManager::~ObjectManager(){
    for (auto object: objects){
        delete object;
    }
}

Rect *ObjectManager::createRect(Point2D center, float width, float height){

    Rect* rect = new Rect(center, width, height);
    objects.push_back(rect);
    renderer->addRigBodyToPtrs(rect);
    addPtrToManagers(rect);
    return rect;
}

Circle *ObjectManager::createCircle(Point2D center, float radius){
    Circle* circle = new Circle(center, radius);
    objects.push_back(circle);
    renderer->addRigBodyToPtrs(circle);
    addPtrToManagers(circle);
    return circle;
}

Softbody *ObjectManager::createSoftRect(Point2D center, float width, float height){
    Softbody* softbodyRect = new SoftbodyRect(center, width, height);
    objects.push_back(softbodyRect);
    renderer->addSoftBodyToPtrs(softbodyRect);
    addPtrToManagers(softbodyRect);
    return softbodyRect;
}

Softbody *ObjectManager::createSoftCircle(Point2D center, float radius, int numPoints){
    Softbody* softbodyCircle = new SoftbodyCircle(center, radius, numPoints);
    objects.push_back(softbodyCircle);
    renderer->addSoftBodyToPtrs(softbodyCircle);
    addPtrToManagers(softbodyCircle);
    return softbodyCircle;
}

Softbody *ObjectManager::createSoftCell(Point2D center, float radius, float stiffness){
    Softbody* softbodyCell = new SoftbodyCell(center, radius, stiffness);
    objects.push_back(softbodyCell);
    renderer->addSoftBodyToPtrs(softbodyCell);
    addPtrToManagers(softbodyCell);
    return softbodyCell;
}

SoftbodyPoint *ObjectManager::getSoftbodyPointContaining(Point2D containedCoords){
    for (auto collObject: objects){
        if (collObject->getObjectType() == ObjectType::SOFTBODY){
            SoftbodyPoint* capturedPoint = ((Softbody*)collObject)->getPointIfCollisionShapeContains(containedCoords);
            if (capturedPoint == nullptr){
                continue;
            } 
            return capturedPoint;
        }
    }
    return nullptr;
}  

void ObjectManager::addPtrToManagers(CollidableObject *ptr){
    collisionManager->addObject(ptr);
    physicsManager->addObject(ptr);
}

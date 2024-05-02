#include "CollidableObject.h"

CollidableObject::~CollidableObject(){
    destroyCollisionShape();
}

ObjectType CollidableObject::getObjectType(){
    return objType;
}

void CollidableObject::setCollisionShape(CollisionShape *collisionShape){
    if ( this->collisionShape != nullptr ) {
        delete this->collisionShape;
    }
    this->collisionShape = collisionShape;
}

CollisionShape *CollidableObject::getCollisionShape(){
    return collisionShape;
}

void CollidableObject::destroyCollisionShape(){
    if (collisionShape != nullptr) {
        delete collisionShape;
        collisionShape = nullptr;
    }
}
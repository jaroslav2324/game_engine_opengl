#pragma once

#include "../physics/CollisionShape.h"

enum class ObjectType {
    RIGIDBODY,
    SOFTBODY,
    UNDEFINED
};

// Collidable object
class CollidableObject {
public:
    CollidableObject(ObjectType type): objType(type){};
    ~CollidableObject();

    ObjectType getObjectType();

    void setCollisionShape (CollisionShape* collisionShape);
    CollisionShape* getCollisionShape();
    void destroyCollisionShape ();

protected:
    ObjectType objType;
    CollisionShape* collisionShape = nullptr;
};
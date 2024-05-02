#pragma once

enum class ObjectType {
    RIGIDBODY,
    SOFTBODY,
    UNDEFINED
};

// Collidable object
class CollidableObject {
    public:
        CollidableObject(ObjectType type): objType(type){};

        ObjectType getObjectType();

    protected:
        ObjectType objType;
};
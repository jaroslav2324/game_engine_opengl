#pragma once

enum class ObjectType {
    RIGIDBODY,
    SOFTBODY,
    UNDEFINED
};

class Object {
    public:
        Object(ObjectType type): objType(type){};

        ObjectType getObjectType();

    protected:
        ObjectType objType;
};
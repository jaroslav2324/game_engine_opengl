#pragma once

#include "../maths/Point2D.h"
#include "AABB.h"

enum class CollisionShapeTypes{
    CIRCLE,
    UNDEFINED
};

class CollisionShape
{

public:
    CollisionShape(Point2D& positionRef): position(positionRef){};
    virtual AABB getAABB() = 0;
    CollisionShapeTypes getShapeType();
    Point2D getPosition();
    void setPosition(Point2D& position);
protected:
    Point2D position; // center
    CollisionShapeTypes shapeType = CollisionShapeTypes::UNDEFINED;

};


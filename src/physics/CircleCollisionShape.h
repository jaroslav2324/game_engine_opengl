#pragma once

#include "CollisionShape.h"

class CircleCollisionShape: public CollisionShape{
public:
    CircleCollisionShape(Point2D& center, float radius): radius(radius), CollisionShape(center, CollisionShapeTypes::CIRCLE){};
    float getRadius();
    void setRadius(float radius);
    virtual AABB getAABB();

    protected:
    float radius;
};



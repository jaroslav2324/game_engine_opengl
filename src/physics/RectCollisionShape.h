#pragma once

#include "CollisionShape.h"
#include "../maths/mathsRect.h"

class RectCollisionShape : public CollisionShape {
public:
    RectCollisionShape(Point2D& center, float width, float height); 

    virtual AABB getAABB();
    mathsRect getMathsRect();

    void setWidth(float width);
    void setHeight(float height);

    float getWidth();
    float getHeight();

private:
    float width;
    float height;
};
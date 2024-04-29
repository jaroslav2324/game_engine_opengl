#include "RectCollisionShape.h"


RectCollisionShape::RectCollisionShape(Point2D &center, float width, float height)
: CollisionShape(position, CollisionShapeTypes::RECT)
{
    this->width = width;
    this->height = height;
}

AABB RectCollisionShape::getAABB()
{
    return AABB(position.x - width / 2, position.y - height / 2, width, height);
}

void RectCollisionShape::setWidth(float width)
{
    this->width = width;
}
void RectCollisionShape::setHeight(float height)
{
    this->height = height;
}

float RectCollisionShape::getWidth()
{
    return width;
}
float RectCollisionShape::getHeight()
{
    return height;
}

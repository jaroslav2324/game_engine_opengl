#include "CollisionShape.h"

CollisionShapeTypes CollisionShape::getShapeType(){
    return shapeType;
}

Point2D CollisionShape::getPosition(){
    return position;
}

void CollisionShape::setPosition(Point2D &position)
{
    this->position = position;
}

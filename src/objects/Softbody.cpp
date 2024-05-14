#include "Softbody.h"



void Softbody::setGravityScale(float gravityScale){
    for(auto& point: points){
        point.physicsParameters.gravityScale = gravityScale;
    }
}

void Softbody::applyPhysics(float deltaTime){
    for(auto& spr: springs){
        spr.updatePhysics();
    }
    for(auto& point: points){
        point.applyPhysics(deltaTime);
    }
}

void Softbody::addVelocity(Vector2D vel){
    for (auto& point: points){
        point.physicsParameters.velocityVec += vel;
    }
}

void Softbody::setStiffness(float stiffness){
    for(auto& spr: springs){
        spr.stiffness = stiffness;
        }
}

std::vector<SoftbodyPoint> &Softbody::getPoints(){
    return points;
}

std::vector<SoftbodySpring> &Softbody::getSprings(){
    return springs;
}

SoftbodyPoint *Softbody::getPointIfCollisionShapeContains(Point2D containsThis){
    for (auto& point: points){
        if (point.coordsInsideCollidableArea(containsThis)){
            return &point;
        }
    }
    return nullptr;
}

ColorRGB Softbody::getTrianglesColor(){
    return trianglesColor;
}

ColorRGB Softbody::getPointsColor(){
    return pointCollidersColor;
}

ColorRGB Softbody::getSpringsColor(){
    return springsColor;
}

void Softbody::setTrianglesColor(ColorRGB color){
    trianglesColor = color;
}

void Softbody::setPointsColor(ColorRGB color){
    pointCollidersColor = color;
}

void Softbody::setSpringsColor(ColorRGB color){
    springsColor = color;
}

void Softbody::setRenderSprings(bool value){
    renderSprings = value;
}

bool Softbody::isSetRenderSprings(){
    return renderSprings;
}

void Softbody::setRenderPoints(bool value){
    renderPoints = value;
}

bool Softbody::isSetRenderPoints(){
    return renderPoints;
}

void Softbody::setDebugDrawAABB(bool value){
    debugDrawAABB = value;
}

bool Softbody::isSetDebugDrawAABB(){
    return debugDrawAABB;
}

AABB Softbody::getAABB(){
    if (points.size() <= 0){
        return AABB(0, 0, 0, 0);
    }

    float minX, maxX, minY, maxY;
    minX = maxX = points[0].position.x;
    minY = maxY = points[0].position.y;
    maxX = minX;
    maxY = minY;
    for (auto point: points){
        if (point.position.x - point.collisionShape.radius < minX){
            minX = point.position.x - point.collisionShape.radius;
        }
        if (point.position.x + point.collisionShape.radius > maxX){
            maxX = point.position.x + point.collisionShape.radius;
        }
        if (point.position.y - point.collisionShape.radius < minY){
            minY = point.position.y - point.collisionShape.radius; 
        }
        if (point.position.y + point.collisionShape.radius > maxY){
            maxY = point.position.y + point.collisionShape.radius;
        }
    }

    return AABB(minX, minY, maxX - minX, maxY - minY);
}

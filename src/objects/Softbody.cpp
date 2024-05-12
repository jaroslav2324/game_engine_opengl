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

std::vector<SoftbodyPoint> &Softbody::getPoints(){
    return points;
}

std::vector<SoftbodySpring> &Softbody::getSprings(){
    return springs;
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
        if (point.position.x < minX){
            minX = point.position.x;
        }
        if (point.position.x > maxX){
            maxX = point.position.x;
        }
        if (point.position.y < minY){
            minY = point.position.y;
        }
        if (point.position.y > maxY){
            maxY = point.position.y;
        }
    }

    return AABB(minX, minY, maxX - minX, maxY - minY);
}

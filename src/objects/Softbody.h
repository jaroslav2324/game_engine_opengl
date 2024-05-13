#pragma once
#include <vector>

#include "../softbody/SoftbodyPoint.h"
#include "../softbody/SoftbodySpring.h"
#include "../maths/Segment2D.h" 
#include "../utils/Color.h"
#include "CollidableObject.h"

enum class SoftbodyType{
    SOFTBODY_CIRCLE,
    SOFTBODY_RECT,
    UNDEFINED
};

class Softbody : public CollidableObject{
public:
    Softbody(SoftbodyType softType)
    : softbodyType(softType), CollidableObject(ObjectType::SOFTBODY){};
    void setGravityScale(float gravityScale);

    void applyPhysics(float deltaTime);
    void addVelocity(Vector2D vel);

    std::vector<SoftbodyPoint>& getPoints();
    std::vector<SoftbodySpring>& getSprings();

    SoftbodyPoint* getPointIfCollisionShapeContains(Point2D containsThis);

    ColorRGB getTrianglesColor();
    ColorRGB getPointsColor();
    ColorRGB getSpringsColor();
    void setTrianglesColor(ColorRGB color);
    void setPointsColor(ColorRGB color);
    void setSpringsColor(ColorRGB color);

    void setRenderSprings(bool value);
    bool isSetRenderSprings();
    void setRenderPoints(bool value);
    bool isSetRenderPoints();

    AABB getAABB();

protected:

    std::vector<SoftbodySpring> springs;
    std::vector<SoftbodyPoint> points;

    ColorRGB trianglesColor;
    ColorRGB springsColor;
    ColorRGB pointCollidersColor; 

    bool renderSprings = true;
    bool renderPoints = true;

    SoftbodyType softbodyType = SoftbodyType::UNDEFINED;
};



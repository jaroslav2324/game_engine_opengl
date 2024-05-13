#pragma once

#include <vector>

#include "../objects/Circle.h"
#include "../objects/Rect.h"
#include "../objects/SoftbodyRect.h"
#include "../maths/Matrix2x2.h"
#include "../maths/mathsCircle.h"


class CollisionManager{
public:
    //CollisionManager();
    //~CollisionManager();
    
    void addObject(CollidableObject* obj);
    void removeObject(CollidableObject* obj);

    void resolveCollisions();

    private:

    void resolveRigidRigidCollision(RigidBody& obj1, RigidBody& obj2);
    void resolveCircleCircleCollision(Circle& cir1, Circle& cir2);
    void resolveCircleRectCollision(Circle& obj1, Rect& obj2); 
    void resolveRectRectCollision(Rect& obj1, Rect& obj2);

    bool checkCircleCircleIntersection( Circle& obj1, Circle& obj2);
    bool checkCircleRectIntersection (Circle& obj1, Rect& obj2);
    bool checkAABBintersection(const AABB& a, const AABB& b);
    bool checkSoftPointRectIntersection(SoftbodyPoint& point, Rect& rect);

    void checkResolveSoftRectCollision(Softbody& soft, Rect& rect);
    Vector2D getCircleRectIntersectionLineVec(Circle& cir, Rect& rect);
    Vector2D getRectRectIntersectionLineVec(Rect& rect1, Rect& rect2);
    Vector2D getSoftPointRectIntersectionLineVec(SoftbodyPoint& point, Rect& rect);

    void pushCirclesApart(Circle& cir1, Circle& cir2);
    void pushCirFromStaticCir(Circle& cir1, Circle& staticCir);
    void pushCirFromStaticRect(Circle& cir, Rect& staticRect, Vector2D shiftAlongNormal);
    void pushSoftPointFromStaticRect(SoftbodyPoint& point, Rect& rect, Vector2D shiftAlongNormal);

    Vector2D reflectVelocityIfDirectsAgainstNormal(Vector2D vel, Vector2D normalReflectOver);

    bool checkObjAABBintersect(CollidableObject& obj1, CollidableObject& obj2);

    // simple velocity multiplication on elasticity coeff
    void applyCollisionEnergyLoss(RigidBody& body);

    std::vector<CollidableObject*> collidableObjects;

};

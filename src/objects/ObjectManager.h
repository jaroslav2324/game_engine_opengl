#pragma once

#include "../rendering/Renderer.h"
#include "../physics/CollisionManager.h"
#include "../physics/PhysicsManager.h"

class ObjectManager
{
public:
    ObjectManager(Renderer* renderer, CollisionManager* collisionManager, PhysicsManager* physicsManager);
    ~ObjectManager();

    Rect* createRect(Point2D center, float width, float height);
    Circle* createCircle(Point2D center, float radius);



private:
    void addPtrToManagers(CollidableObject* ptr);

    std::vector<CollidableObject*> objects;
    Renderer* renderer;
    CollisionManager* collisionManager;
    PhysicsManager* physicsManager;
};


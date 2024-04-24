#include "circle.h"

// Function to apply velocity to the circle and update its position
void Circle::applyVelocity(float dt){

    if (physicsParameters.staticBody == true){
        physicsParameters.velocityVector.x = 0;
        physicsParameters.velocityVector.y = 0;
        return;
    }

    center.x += physicsParameters.velocityVector.x * dt;
    center.y += physicsParameters.velocityVector.y * dt;

    auto collisionCenter = collisionShape.getPosition();
    collisionCenter.x += physicsParameters.velocityVector.x * dt;
    collisionCenter.y += physicsParameters.velocityVector.y * dt;
    collisionShape.setPosition(collisionCenter);

    // Update the rendered triangles
    for (auto& tr: renderedTriangles){
        tr.node1.x += physicsParameters.velocityVector.x * dt;
        tr.node1.y += physicsParameters.velocityVector.y * dt;
        tr.node2.x += physicsParameters.velocityVector.x * dt;
        tr.node2.y += physicsParameters.velocityVector.y * dt;
        tr.node3.x += physicsParameters.velocityVector.x * dt;
        tr.node3.y += physicsParameters.velocityVector.y * dt;
    }
}

void Circle::applyGravity(float dt){
    physicsParameters.forceVector.y += G * physicsParameters.mass * physicsParameters.gravityScale * dt;
}

void Circle::applyForces(float dt)
{
    if (physicsParameters.staticBody == true){
        physicsParameters.forceVector.x = 0;
        physicsParameters.forceVector.y = 0;
        return;
    }
    // change velocity based on force
    physicsParameters.velocityVector.x += physicsParameters.forceVector.x * dt;
    physicsParameters.velocityVector.y += physicsParameters.forceVector.y * dt;

    // reset force vector

    physicsParameters.forceVector.x = 0;
    physicsParameters.forceVector.y = 0;
    applyGravity(dt);
    // apply other forces
}

std::vector<Point2D> Circle::generatePointsOnCircle(int num_points)
{
    std::vector<Point2D> points;
    float angle_increment = 2 * M_PI / num_points;

    for (int i = 0; i < num_points; ++i) {
        float angle = i * angle_increment;
        float x = center.x + radius * cos(angle);
        float y = center.y + radius * sin(angle);
        points.push_back(Point2D(x, y));
    }

    return points;
}

Circle::Circle(Point2D center, float radius): 
collisionShape(center, radius){

    this->center = center;
    this->radius = radius;
    color.r = 0.7f;
    color.g = 0.7f;
    color.b = 0.7f;
    edgesColor.r = 1.0f;
    edgesColor.g = 1.0f;
    edgesColor.b = 1.0f;

    std::vector<Point2D> points;
    points = generatePointsOnCircle(16);//generateRandomPoints(10, center, -100, 100, -100, 100);
    points.push_back(center);
    renderedTriangles = triangulateBowyerWatson(points);
}

std::vector<NodesEdgesTriangles> &Circle::getRenderedTriangles(){
    return renderedTriangles;
}

void Circle::setCircleColor(ColorRGB &color){
    this->color = color;
}

void Circle::setEdgesColor(ColorRGB &color){
    this->edgesColor = color;
}

ColorRGB Circle::getCircleColor(){
    return color;
}

ColorRGB Circle::getEdgesColor(){
    return edgesColor;
}

CircleCollisionShape &Circle::getCollisionShape(){
    return collisionShape;
}

void Circle::applyPhysics(float dt)
{
    applyVelocity(dt);
    applyForces(dt);
}

#include "Circle.h"

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

Circle::Circle(Point2D center, float radius): RigidBody(center, RigidBodyType::CIRCLE) {

    setCollisionShape(new CircleCollisionShape(center, radius));
    this->radius = radius;
    color.r = 0.7f;
    color.g = 0.7f;
    color.b = 0.7f;
    edgesColor.r = 1.0f;
    edgesColor.g = 1.0f;
    edgesColor.b = 1.0f;

    std::vector<Point2D> points;
    points = generatePointsOnCircle(16);
    points.push_back(center);
    renderedTriangles = triangulateBowyerWatson(points);
}

void Circle::updateRenderedItemsPosition(float dx, float dy)
{
    for (auto& tr: renderedTriangles){
        tr.node1.x += dx;
        tr.node1.y += dy;
        tr.node2.x += dx;
        tr.node2.y += dy;
        tr.node3.x += dx;
        tr.node3.y += dy;
    }
}

std::vector<NodesEdgesTriangles> &Circle::getRenderedTriangles()
{
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

void Circle::setRadius(float radius){
    this->radius = radius;
}

float Circle::getRadius(){
    return radius;
}

void Circle::setRenderEdges(bool renderEdges){
    this->renderEdges = renderEdges;
}

bool Circle::isSetEdgesRendered(){
    return this->renderEdges;
}

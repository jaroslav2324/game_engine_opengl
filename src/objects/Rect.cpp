#include "Rect.h"

Rect::Rect(Point2D center, float width, float height)
:  RigidBody(center, RigidBodyType::RECT)
{
    setCollisionShape(new RectCollisionShape(center, width, height));

    this->width = width;
    this->height = height;

    color.r = 0.7f;
    color.g = 0.7f;
    color.b = 0.7f;
    edgesColor.r = 1.0f;
    edgesColor.g = 1.0f;
    edgesColor.b = 1.0f;

    std::vector<Point2D> points;
    points.push_back(Point2D(center.x - width/2, center.y - height/2));
    points.push_back(Point2D(center.x + width/2, center.y - height/2));
    points.push_back(Point2D(center.x + width/2, center.y + height/2)); 
    points.push_back(Point2D(center.x - width/2, center.y + height/2));

    renderedTriangles = triangulateBowyerWatson(points);
}

void Rect::updateRenderedItemsPosition(float dx, float dy){
    for (auto& tr: renderedTriangles){
        tr.node1.x += dx;
        tr.node1.y += dy;
        tr.node2.x += dx;
        tr.node2.y += dy;
        tr.node3.x += dx;
        tr.node3.y += dy;
    }
}

std::vector<NodesEdgesTriangles> &Rect::getRenderedTriangles(){
    return renderedTriangles;
}

void Rect::setRectColor(ColorRGB color){
    this->color = color;
}

void Rect::setEdgesColor(ColorRGB color){
    this->edgesColor = color;
}

ColorRGB Rect::getRectColor(){
    return color;
}

ColorRGB Rect::getEdgesColor(){
    return edgesColor;
}
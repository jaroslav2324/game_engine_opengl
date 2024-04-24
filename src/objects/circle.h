#pragma once

#include <vector>
#include <cmath>

#include "../triangulation/structures.h"
#include "../triangulation/triangulation.h"
#include "../maths/Point2D.h"
#include "../utils/Color.h"
#include "../physics/CircleCollisionShape.h"

class Renderer;


class Circle{
    public:

    Circle(Renderer* renderer, Point2D center, float radius);

    // int debug_stage = 0;
    // int debug_IdxNextRenderedPoint = -1;
    // std::vector<Point2D> debug_allPoints;
    // std::vector<Point2D> debug_renderedPoints;
    // void debug_insertNextPointInTriang();

    std::vector<NodesEdgesTriangles>& getRenderedTriangles();
    // TODO add circle points and setter
    void setCircleColor(ColorRGB& color);
    void setEdgesColor(ColorRGB& color);
    ColorRGB getCircleColor();
    ColorRGB getEdgesColor();
    CircleCollisionShape& getCollisionShape();

    private:

    std::vector<Point2D> generatePointsOnCircle(int num_points);

    Point2D center;
    float radius;
    std::vector<NodesEdgesTriangles> renderedTriangles;
    ColorRGB color;
    ColorRGB edgesColor;

    CircleCollisionShape collisionShape;

};
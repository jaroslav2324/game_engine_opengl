#pragma once

#include <vector>
#include <cmath>

#include "../triangulation/structures.h"
#include "../triangulation/triangulation.h"
#include "../maths/Point2D.h"
#include "../utils/Color.h"
#include "../physics/CircleCollisionShape.h"
#include "../physics/PhysicsParameters.h"
#include "RigidBody.h"


class Circle: public RigidBody{
    public:

    Circle(Point2D center, float radius);

    virtual void updateRenderedItemsPosition (float dx, float  dy);

    std::vector<NodesEdgesTriangles>& getRenderedTriangles();
    void setCircleColor(ColorRGB& color);
    void setEdgesColor(ColorRGB& color);
    ColorRGB getCircleColor();
    ColorRGB getEdgesColor();

    void setRenderEdges(bool renderEdges);
    bool isSetEdgesRendered();

    private:

    bool renderEdges = false;

    std::vector<Point2D> generatePointsOnCircle(int num_points);

    float radius;
    std::vector<NodesEdgesTriangles> renderedTriangles;
    ColorRGB color;
    ColorRGB edgesColor;
};
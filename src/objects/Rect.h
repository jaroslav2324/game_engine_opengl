#pragma once

#include <vector>

#include "RigidBody.h"
#include "../utils/Color.h"
#include "../triangulation/triangulation.h"


class Rect: public RigidBody {
    public:
    Rect(Point2D& center, float width, float height);

    virtual void updateRenderedItemsPosition (float dx, float  dy);

    std::vector<NodesEdgesTriangles>& getRenderedTriangles();

    void setColor(ColorRGB color);
    void setEdgesColor(ColorRGB color);

    private:

    float width;
    float height;

    std::vector<NodesEdgesTriangles> renderedTriangles;

    ColorRGB color;
    ColorRGB edgesColor;
};

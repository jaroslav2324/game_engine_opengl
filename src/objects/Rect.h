#pragma once

#include <vector>

#include "RigidBody.h"
#include "../utils/Color.h"
#include "../triangulation/triangulation.h"
#include "../physics/RectCollisionShape.h"
#include "../maths/Segment2D.h" 
#include "../maths/mathsRect.h" 


class Rect: public RigidBody {
    public:
    Rect(Point2D center, float width, float height);

    virtual void updateRenderedItemsPosition (float dx, float  dy);

    std::vector<NodesEdgesTriangles>& getRenderedTriangles();

    void setRectColor(ColorRGB color);
    void setEdgesColor(ColorRGB color);
    ColorRGB getRectColor();
    ColorRGB getEdgesColor();

    float getWidth();
    float getHeight();
    mathsRect getMathsRect();
    // fills segs 
    void getSegments(Segment2D* segs);

    void setRenderEdges(bool renderEdges);
    bool isSetEdgesRendered();

    private:

    bool renderEdges = false;

    float width;
    float height;

    std::vector<NodesEdgesTriangles> renderedTriangles;

    ColorRGB color;
    ColorRGB edgesColor;
};

#pragma once
#include "Point2D.h" 
#include "Vector2D.h"
#include "mathsCircle.h"

struct mathsRect{
    mathsRect();
    mathsRect(float x, float y, float width, float height);
    mathsRect(Point2D upperLeft, float width, float height);

    void getSegments(Segment2D* segs); 
    Vector2D getIntersectionLineVecCircle(mathsCircle& circle);
    Vector2D getIntersectionLineVecRect(mathsRect& rect);

    float x, y;
    float width, height;
};

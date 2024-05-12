#pragma once
#include "Point2D.h"

struct Segment2D{
    Segment2D(Point2D p1, Point2D p2): p1(p1), p2(p2){};
    Point2D p1;
    Point2D p2;
};
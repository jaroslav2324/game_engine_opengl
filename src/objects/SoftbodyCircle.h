#pragma once

#include "Softbody.h"
#include "../utils/pointsGeneration.h"

class SoftbodyCircle: public Softbody{
public:
    SoftbodyCircle(Point2D center, float radius, int numPoints);
    float getRadius();

private:
    float radius;
};
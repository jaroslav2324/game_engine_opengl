#pragma once

#include "Softbody.h"
#include "../utils/pointsGeneration.h"

class SoftbodyCell: public Softbody{
public:
    SoftbodyCell(Point2D center, float radius);
private:
    float outerRadius;
    float innerRadius;
};
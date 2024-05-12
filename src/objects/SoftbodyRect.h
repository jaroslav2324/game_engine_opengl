#pragma once

#include "Softbody.h"

class SoftbodyRect: public Softbody{
public:
    SoftbodyRect(Point2D center, float width, float height);

    float getWidth();
    float getHeight();

private:
    float width;
    float height;
};
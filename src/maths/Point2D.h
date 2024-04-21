#pragma once

#include "../triangulation/structures.h"

typedef struct Point2D{
    Point2D(): x(0), y(0){};
    Point2D(float x, float y): x(x), y(y){};
    float x;
    float y;

    operator Node() const{
        return Node(x, y);
    }
} Point2D;

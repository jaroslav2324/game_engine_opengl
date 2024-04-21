#pragma once

#include <vector>

#include "../triangulation/structures.h"
#include "../triangulation/triangulation.h"
#include "../maths/Point2D.h"

class Renderer;


class Circle{
    public:

    Circle(Renderer* renderer, Point2D center);

    std::vector<NodesEdgesTriangles>& getRenderedTriangles();

    private:
    Point2D center;
    std::vector<NodesEdgesTriangles> renderedTriangles;
};
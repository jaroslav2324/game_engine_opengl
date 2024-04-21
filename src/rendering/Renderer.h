#pragma once

#include <vector>
#include <algorithm>

#include <GL/glut.h>

#include "../objects/circle.h"
#include "../triangulation/structures.h"



class Renderer{
    public:

    Renderer(int winWidth, int winHeight): winWidth(winWidth), winHeight(winHeight){};

    void render();

    void addCircleToPtrs(Circle* circle);
    void removeCircleFromPtrs(Circle* circle);

    private:

    void drawCircles();
    void drawCircle(Circle* circle);
    void drawTriangs(std::vector<NodesEdgesTriangles>& trianglesVec);
    void drawEdges(std::vector<NodesEdgesTriangles>& trianglesVec);

    Node coordsToNormed(Node& node);

    // TODO create abstract object?
    std::vector<Circle*> circlePtrs;

    int winWidth, winHeight;
};
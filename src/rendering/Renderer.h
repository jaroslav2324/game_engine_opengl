#pragma once

#include <vector>
#include <algorithm>

#include <GL/glut.h>

#include "../objects/Circle.h"
#include "../objects/Rect.h"
#include "../triangulation/structures.h"



class Renderer{
    public:

    Renderer(int winWidth, int winHeight): winWidth(winWidth), winHeight(winHeight){};

    void render();
    // ??
    void renderTriangles(std::vector<NodesEdgesTriangles>& triangles);    

    void addRigBodyToPtrs(RigidBody* body);
    void removeRigBodyFromPtrs(RigidBody* body);

    private:

    void setOpenGLColor(ColorRGB& color);
    void drawRigidBodies();
    void drawCircle(Circle* circle);
    void drawRect(Rect* rect);
    void drawTriangs(std::vector<NodesEdgesTriangles>& trianglesVec);
    void drawEdges(std::vector<NodesEdgesTriangles>& trianglesVec);

    Node coordsToNormed(Node& node);

    // TODO create abstract object?
    // std::vector<Circle*> circlePtrs;
    std::vector<RigidBody*> rigidBodies;

    int winWidth, winHeight;
};
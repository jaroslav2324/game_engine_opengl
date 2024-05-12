#pragma once

#include <vector>
#include <algorithm>

#include <GL/glut.h>

#include "../objects/Circle.h"
#include "../objects/Rect.h"
#include "../objects/SoftbodyRect.h"
#include "../triangulation/structures.h"



class Renderer{
    public:

    Renderer(int winWidth, int winHeight): winWidth(winWidth), winHeight(winHeight){};

    void render();
    // ??
    void renderTriangles(std::vector<NodesEdgesTriangles>& triangles);    

    void addRigBodyToPtrs(RigidBody* body);
    void removeRigBodyFromPtrs(RigidBody* body);
    void addSoftBodyToPtrs(Softbody* body);
    void removeSoftBodyFromPtrs(Softbody* body);

    private:

    void setOpenGLColor(ColorRGB& color);
    void drawRigidBodies();
    void drawSoftBodies();
    void drawCircle(Circle* circle);
    void drawRect(Rect* rect);
    void drawTriangs(std::vector<NodesEdgesTriangles>& trianglesVec);
    void drawEdges(std::vector<NodesEdgesTriangles>& trianglesVec);
    void drawSoftPoint(SoftbodyPoint& point);
    void drawSoftSpring(SoftbodySpring& spring);

    Node coordsToNormed(Node& node);
    Point2D coordsToNormed(Point2D& point);

    // TODO create abstract object?
    std::vector<RigidBody*> rigidBodies;
    std::vector<Softbody*> softBodies;

    int winWidth, winHeight;

    const int softbodyCircleSegments = 16;
};
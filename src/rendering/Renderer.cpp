#include "Renderer.h"

void Renderer::render(){
    drawRigidBodies();
    drawSoftBodies();
}

void Renderer::renderTriangles(std::vector<NodesEdgesTriangles>& triangles){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.7f, 0.0f, 0.7f);
    drawTriangs(triangles);
    glColor3f(0.0f, 0.7f, 0.7f);
    drawEdges(triangles);
    //glFlush();
    glFinish();
}

void Renderer::addRigBodyToPtrs(RigidBody *body){
    rigidBodies.push_back(body);
}

void Renderer::removeRigBodyFromPtrs(RigidBody *body){
    rigidBodies.erase(std::remove(rigidBodies.begin(), rigidBodies.end(), body), rigidBodies.end());
}

void Renderer::addSoftBodyToPtrs(Softbody *body){
    softBodies.push_back(body);
}

void Renderer::removeSoftBodyFromPtrs(Softbody *body){
    softBodies.erase(std::remove(softBodies.begin(), softBodies.end(), body), softBodies.end());
}

void Renderer::setOpenGLColor(ColorRGB &color){
    glColor3f(color.r, color.g, color.b);
}

void Renderer::drawRigidBodies(){

    for (auto bodyPtr: rigidBodies){
        RigidBodyType type = bodyPtr->getRigBodyType();
        if (type == RigidBodyType::CIRCLE){
            drawCircle((Circle*)bodyPtr);
        }
        else if (type == RigidBodyType::RECT){
            drawRect((Rect*)bodyPtr);
        }
        else{
            // TODO add error handling
        }
    }
}

void Renderer::drawSoftBodies(){
    for (auto bodyPtr: softBodies){
        if (bodyPtr->isSetRenderPoints()){
            ColorRGB pointsColor = bodyPtr->getPointsColor();
            setOpenGLColor(pointsColor);
            auto points = bodyPtr->getPoints();
            for (auto point: points){  
                drawSoftPoint(point);
            }
        }
        if (bodyPtr->isSetRenderSprings()){
            ColorRGB springsColor = bodyPtr->getSpringsColor();
            setOpenGLColor(springsColor);
            auto springs = bodyPtr->getSprings();
            for (auto spring: springs){
                drawSoftSpring(spring);
            }
        }
        if (bodyPtr->isSetDebugDrawAABB()){
            ColorRGB aabbColor(255, 0, 0);
            setOpenGLColor(aabbColor);
            auto aabb = bodyPtr->getAABB();
            drawAABB(aabb);
        }
    }
}

void Renderer::drawCircle(Circle *circle){
    ColorRGB color = circle->getCircleColor();
    setOpenGLColor(color);
    drawTriangs(circle->getRenderedTriangles());

    if (circle->isSetEdgesRendered()){
        ColorRGB edgeColor = circle->getEdgesColor();
        setOpenGLColor(edgeColor);
        drawEdges(circle->getRenderedTriangles());
    }
}

void Renderer::drawRect(Rect *rect){
    ColorRGB color = rect->getRectColor();
    setOpenGLColor(color);
    drawTriangs(rect->getRenderedTriangles());
    
    if (rect->isSetEdgesRendered()){
        ColorRGB edgeColor = rect->getEdgesColor();
        setOpenGLColor(edgeColor);
        drawEdges(rect->getRenderedTriangles());
    }
}

void Renderer::drawAABB(AABB &aabb){
    Point2D p1(aabb.x, aabb.y);
    Point2D p2(aabb.x + aabb.w, aabb.y);
    Point2D p3(aabb.x + aabb.w, aabb.y + aabb.h);
    Point2D p4(aabb.x, aabb.y + aabb.h);
    auto norm1 = coordsToNormed(p1);
    auto norm2 = coordsToNormed(p2);
    auto norm3 = coordsToNormed(p3);
    auto norm4 = coordsToNormed(p4);
    glBegin(GL_LINES);
    glVertex2f(norm1.x, norm1.y);
    glVertex2f(norm2.x, norm2.y);
    glVertex2f(norm2.x, norm2.y);
    glVertex2f(norm3.x, norm3.y);
    glVertex2f(norm3.x, norm3.y);
    glVertex2f(norm4.x, norm4.y);
    glVertex2f(norm4.x, norm4.y);
    glVertex2f(norm1.x, norm1.y);
   glEnd();
}

void Renderer::drawTriangs(std::vector<NodesEdgesTriangles> &trianglesVec){

    glBegin(GL_TRIANGLES);
    for (auto & tr: trianglesVec){
        auto normN1 = coordsToNormed(tr.node1);
        auto normN2 = coordsToNormed(tr.node2);
        auto normN3 = coordsToNormed(tr.node3);
        glVertex2d(normN1.x, normN1.y);
        glVertex2d(normN2.x, normN2.y);
        glVertex2d(normN3.x, normN3.y);
    }
    glEnd();
}

void Renderer::drawEdges(std::vector<NodesEdgesTriangles> &trianglesVec){
    glBegin(GL_LINES);
    for (auto& tr: trianglesVec){
        auto normN1 = coordsToNormed(tr.node1);
        auto normN2 = coordsToNormed(tr.node2);
        auto normN3 = coordsToNormed(tr.node3);
        glVertex2d(normN1.x, normN1.y);
        glVertex2d(normN2.x, normN2.y);
        glVertex2d(normN2.x, normN2.y);
        glVertex2d(normN3.x, normN3.y);
        glVertex2d(normN3.x, normN3.y);
        glVertex2d(normN1.x, normN1.y);
   }
   glEnd();
}

void Renderer::drawSoftPoint(SoftbodyPoint &point){

    float radius = point.collisionShape.radius;
    Point2D center = point.position;

    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < softbodyCircleSegments; i++)
    {
        float theta = 2.0f * 3.1415926f * float(i) / float(softbodyCircleSegments);
        float x = radius * cosf(theta);
        float y = radius * sinf(theta);
        Point2D normedCoords(x + center.x, y + center.y);
        normedCoords = coordsToNormed(normedCoords);
        glVertex2f(normedCoords.x, normedCoords.y);
    }
    glEnd();
}

void Renderer::drawSoftSpring(SoftbodySpring &spring){
    Point2D p1 = spring.point1->position;
    Point2D p2 = spring.point2->position;
    Point2D normed1 = coordsToNormed(p1);
    Point2D normed2 = coordsToNormed(p2);
    glBegin(GL_LINES);
    glVertex2f(normed1.x, normed1.y);
    glVertex2f(normed2.x, normed2.y);
    glEnd();
}

// maps pixel coords to -1 to 1 (physical coords to viewport coords)
Node Renderer::coordsToNormed(Node& node){

    Node normedNode;
    // 0 - min value
    normedNode.x = -1.0 + 2.0 * (node.x - 0) / (float)(winWidth - 0);
    normedNode.y =  2 * (1 - ((node.y - 0) / (float)(winHeight - 0))) - 1;
    return normedNode;
}

Point2D Renderer::coordsToNormed(Point2D &point){
    Point2D normedPoint;
    normedPoint.x = -1.0 + 2.0 * (point.x - 0) / (float)(winWidth - 0);
    normedPoint.y =  2 * (1 - ((point.y - 0) / (float)(winHeight - 0))) - 1;
    return normedPoint;
}

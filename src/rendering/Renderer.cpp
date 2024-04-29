#include "Renderer.h"

void Renderer::render(){
    glClear(GL_COLOR_BUFFER_BIT);
    drawRigidBodies();
    glFlush();
}

void Renderer::renderTriangles(std::vector<NodesEdgesTriangles>& triangles){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.7f, 0.0f, 0.7f);
    drawTriangs(triangles);
    glColor3f(0.0f, 0.7f, 0.7f);
    drawEdges(triangles);
    glFlush();
}

void Renderer::addRigBodyToPtrs(RigidBody *body){
    rigidBodies.push_back(body);
}

void Renderer::removeRigBodyFromPtrs(RigidBody *body){
    rigidBodies.erase(std::remove(rigidBodies.begin(), rigidBodies.end(), body), rigidBodies.end());
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

void Renderer::drawCircle(Circle *circle){
    ColorRGB color = circle->getCircleColor();
    setOpenGLColor(color);
    drawTriangs(circle->getRenderedTriangles());
    ColorRGB edgeColor = circle->getEdgesColor();
    setOpenGLColor(edgeColor);
    // TODO add flag if edge drawing is needed
    drawEdges(circle->getRenderedTriangles());
}

void Renderer::drawRect(Rect *rect){
    ColorRGB color = rect->getRectColor();
    setOpenGLColor(color);
    drawTriangs(rect->getRenderedTriangles());
    ColorRGB edgeColor = rect->getEdgesColor();
    setOpenGLColor(edgeColor);
    // TODO add flag if edge drawing is needed
    drawEdges(rect->getRenderedTriangles());
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

// maps pixel coords to -1 to 1 (physical coords to viewport coords)
Node Renderer::coordsToNormed(Node& node){

    Node normedNode;
    // 0 - min value
    normedNode.x = -1.0 + 2.0 * (node.x - 0) / (winWidth - 0);
    normedNode.y =  2 * (1 - ((node.y - 0) / (winHeight - 0))) - 1;
    return normedNode;
}
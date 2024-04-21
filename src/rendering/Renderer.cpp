#include "Renderer.h"

void Renderer::render(){
    glClear(GL_COLOR_BUFFER_BIT);
    drawCircles();
    glFlush();
}

void Renderer::addCircleToPtrs(Circle *circle)
{
    circlePtrs.push_back(circle);
}

void Renderer::removeCircleFromPtrs(Circle *circle){
    circlePtrs.erase(std::remove(circlePtrs.begin(), circlePtrs.end(), circle), circlePtrs.end());
}

void Renderer::drawCircles()
{
    // TODO remove
    srand(time(0));
    for (auto cirPtr: circlePtrs){
        drawCircle(cirPtr);
    }
}

void Renderer::drawCircle(Circle *circle)
{
    //TODO set circle color from circle
    glColor3f(0.7f, 0.7f, 0.0f); 
    drawTriangs(circle->getRenderedTriangles());
    //TODO set edge colour from circle
    glColor3f(1.0f, 1.0f, 0.0f);
    // TODO add flag if edge drawing is needed
    drawEdges(circle->getRenderedTriangles());
}

void Renderer::drawTriangs(std::vector<NodesEdgesTriangles> &trianglesVec)
{

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
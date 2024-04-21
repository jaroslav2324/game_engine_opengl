#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>


#include "triangulation/triangulation.h"

#define WIN_WIDTH 1000
#define WIN_HEIGHT 800

std::vector<Node> points = {
    {50.0f, 100.0f},
    {150.0f, 120.0f},
    {350.0f, 600.0f},
    {150.0f, 500.0f},
    {250.0f, 700.0f}
};

int nextPointIdx = 0;


// maps pixel coords to -1 to 1 (physical coords to viewport coords)
Node coordsToNormed(Node& node){

    Node normedNode;
    // 0 - min value
    normedNode.x = -1.0 + 2.0 * (node.x - 0) / (WIN_WIDTH - 0);
    normedNode.y =  2 * (1 - ((node.y - 0) / (WIN_HEIGHT - 0))) - 1;
    return normedNode;
}

std::vector<NodesEdgesTriangles> displayedTriangulation;

void displayTriangulation(){
   glColor3f(1.0f, 0.0f, 0.0f); // red
   glBegin(GL_TRIANGLES);
   for (auto& tr: displayedTriangulation){
        auto normN1 = coordsToNormed(tr.node1);
        auto normN2 = coordsToNormed(tr.node2);
        auto normN3 = coordsToNormed(tr.node3);
        glVertex2d(normN1.x, normN1.y);
        glVertex2d(normN2.x, normN2.y);
        glVertex2d(normN3.x, normN3.y);
   }
   glEnd();

    glColor3f(1.0f, 1.0f, 0.0f);
   glBegin(GL_LINES);
   for (auto& tr: displayedTriangulation){
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


void displayMe(void) {
    std::cout << "display" << std::endl;
    glClear(GL_COLOR_BUFFER_BIT);
    displayTriangulation();
    glFlush();
}

void myIdleFunc(){

}

void mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        std::cout << "left mouse butoon pressed" << std::endl;

        if (nextPointIdx >= points.size()){
            return;
        }

        insertPointInTriangulation(points[nextPointIdx], displayedTriangulation);
        nextPointIdx++;

        glutPostRedisplay();
    }
}


int main(int argc, char** argv) {

    displayedTriangulation = triangulateBowyerWatson(points);
    //displayedTriangulation.push_back(createSuperTriangle(points));

    // Пример использования
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("");
    //glOrtho(-1, 1, -1, 1, -1, 1); // Установка ортографической проекции
    glutDisplayFunc(displayMe);
    glutIdleFunc(myIdleFunc);
    //glutMouseFunc(mouseClick);
    glutMainLoop();

    return 0;
}
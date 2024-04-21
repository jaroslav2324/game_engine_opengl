#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>


#include "triangulation/triangulation.h"
#include "rendering/Renderer.h"

#define WIN_WIDTH 1000
#define WIN_HEIGHT 800

#define RANDOM_TRIANG_POINTS_TEST true

Renderer renderer(WIN_WIDTH, WIN_HEIGHT);

// // maps pixel coords to -1 to 1 (physical coords to viewport coords)
// Node coordsToNormed(Node& node){

//     Node normedNode;
//     // 0 - min value
//     normedNode.x = -1.0 + 2.0 * (node.x - 0) / (WIN_WIDTH - 0);
//     normedNode.y =  2 * (1 - ((node.y - 0) / (WIN_HEIGHT - 0))) - 1;
//     return normedNode;
// }

std::vector<NodesEdgesTriangles> displayedTriangulation;




void displayMe(void) {
    std::cout << "display" << std::endl;
    renderer.render();
}

void myIdleFunc(){

}

void mouseClick(int button, int state, int x, int y) {

    // if(RANDOM_TRIANG_POINTS_TEST){
    //     points = generateRandomPoints(100, 50, WIN_WIDTH - 50, 50, WIN_HEIGHT - 50);
    //     displayedTriangulation = triangulateBowyerWatson(points);
    //     glutPostRedisplay();
    // }

    // if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    //     std::cout << "left mouse butoon pressed" << std::endl;

    //     if (nextPointIdx >= points.size()){
    //         return;
    //     }

    //     insertPointInTriangulation(Node(points[nextPointIdx]), displayedTriangulation);
    //     nextPointIdx++;

    //     glutPostRedisplay();
    // }
}


int main(int argc, char** argv) {

    Circle cir1(&renderer, Point2D(200, 200));
    Circle cir2(&renderer, Point2D(600, 600));

    renderer.addCircleToPtrs(&cir1);
    renderer.addCircleToPtrs(&cir2);

    // Пример использования
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("");
    //glOrtho(-1, 1, -1, 1, -1, 1); // Установка ортографической проекции
    glutDisplayFunc(displayMe);
    glutIdleFunc(myIdleFunc);
    glutMouseFunc(mouseClick);
    glutMainLoop();

    return 0;
}
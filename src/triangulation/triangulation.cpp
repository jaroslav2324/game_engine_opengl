#include "triangulation.h"

NodesEdgesTriangles createSuperTriangle(std::vector<Node> points)
{
    float maxX = points[0].x, minX = points[0].x, maxY = points[0].y, minY = points[0].y;
    for (auto& point: points){
        if (point.x > maxX)
            maxX = point.x;
        if (point.x < minX)
            minX = point.x;
        if (point.y > maxY)
            maxY = point.y;
        if (point.y < minY)
            minY = point.y;
    }

    float diffY = maxY - minY;
    float diffX = maxX - minX;

    Node nt1, nt2, nt3;

    nt1.x = minX - diffX * 0.2;
    nt1.y = minY - diffY;
    nt2.x = minX - diffX * 0.2;
    nt2.y = minY + diffY * 2;
    nt3.x = minX + diffX * 1.8;
    nt3.y = minY + diffY * 0.5;
    
    return NodesEdgesTriangles(nt1, nt2, nt3);
}



std::vector<NodesEdgesTriangles> triangulateBowyerWatson(std::vector<Point2D> inPoints){

    std::vector<Node> points;
    for (auto& inp: inPoints){
        points.push_back(inp);
    }

    Edge* edgePtrs[3];

    std::vector<NodesEdgesTriangles> triangulation;

    if (points.size() <= 0){
        return triangulation;
    }

    NodesEdgesTriangles superTriangle = createSuperTriangle(points);
    triangulation.push_back(superTriangle);

    for (auto& point: points){
        insertPointInTriangulation(point, triangulation);
    }

    // delete because of superTriangle
    std::vector<int> triangleIndexes;
    int counter = 0;
    for (auto& triangle: triangulation){
        if (triangle.hasNode(superTriangle.node1) || triangle.hasNode(superTriangle.node2) || triangle.hasNode(superTriangle.node3)){
            triangleIndexes.push_back(counter);
        }
        counter++;
    }
    std::reverse(triangleIndexes.begin(), triangleIndexes.end());
    for (auto idx: triangleIndexes){
            triangulation.erase(triangulation.begin() + idx);
    }

    return triangulation;
}

void insertPointInTriangulation(Node point, std::vector<NodesEdgesTriangles> &triangulation)
{
    Edge* edgePtrs[3] = {};


    std::vector<EdgeWithNodes> polygon;

    for (auto& triang: triangulation){

        if (!triang.delaunayCriteriaSatisfied(point)){
            triang.isBad = true;
            polygon.push_back(triang.edge1);
            polygon.push_back(triang.edge2);
            polygon.push_back(triang.edge3);
        }
    }

        triangulation.erase(std::remove_if(begin(triangulation), end(triangulation), [](NodesEdgesTriangles &t){
			return t.isBad;
    }), end(triangulation));

    for (auto e1 = polygon.begin(); e1 != polygon.end(); e1++){
        for (auto e2 = e1 + 1; e2 != polygon.end(); e2++){
            if (*e1 == *e2){
                e1->isBad = true;
                e2->isBad = true;
            }
        }
    }

    polygon.erase(std::remove_if(begin(polygon), end(polygon), [](EdgeWithNodes &e){
			return e.isBad;
		}), end(polygon));

    for(auto& edge: polygon){
        triangulation.push_back(NodesEdgesTriangles(edge.node1, edge.node2, point));
    }


}

// void debug_insertPointInTriangulation(Node point, std::vector<NodesEdgesTriangles> &triangulation, int stage)
// {
//     Edge* edgePtrs[3] = {};

//     if (stage == 0){
//         glColor3f(0.3f, 0.3f, 0.0f); 
//         std::vector<NodesEdgesTriangles>  nw (triangulation.begin(), triangulation.begin() + 1);
//         debug_drawTriangs(nw);
//         glColor3f(0.7f, 0.7f, 0.0f); 
//         std::vector<NodesEdgesTriangles>  nw2 (triangulation.begin() + 1, triangulation.end());
//         debug_drawTriangs(nw2);
//         return;
//     }

//     std::vector<NodesEdgesTriangles> badTriangles;
//     std::vector<int> badIndexes;
//     int counter = 0;
//     for (auto& triang: triangulation){
//         if (triang.hasNode(point)){
//             // skip check
//             counter++;
//             continue;
//         }
//         bool res = !triang.delaunayCriteriaSatisfied(point);
//         if (res){
//             badTriangles.push_back(triang);
//             badIndexes.push_back(counter);
//             std::cout << "\033[91m" << "Delaunay not satisfied!" << "\033[39m" << std::endl;
//         }
//         //std::cout << "\033[91m" << !triang.delaunayCriteriaSatisfied(point) << "\033[39m" << std::endl;
//         counter++;
//     }

//     if (stage == 1){
//         std::vector<NodesEdgesTriangles> good;
//         for (int i = 0; i< triangulation.size(); ++i){
//             if (std::find(badIndexes.begin(), badIndexes.end(), i) == badIndexes.end()){
//                 good.push_back(triangulation[i]);
//             }
//         }

//         glColor3f(0.7f, 0.0f, 0.0f); 
//         debug_drawTriangs(badTriangles);
//         glColor3f(0.0f, 0.7f, 0.0f); 
//         debug_drawTriangs(good);
//         return;
//     }

//     std::vector<Edge*> polygon;
//     for (int i = 0; i < badTriangles.size(); i++){
//         edgePtrs[0] = &badTriangles[i].edge1;
//         edgePtrs[1] = &badTriangles[i].edge2;
//         edgePtrs[2] = &badTriangles[i].edge3;
//         // foreach edge
//         for (int edgeIdx = 0; edgeIdx < 3; edgeIdx++){
//             bool flagAdd = true;
//             for (int j = 0; j < badTriangles.size(); j++){
//                 if (i == j){
//                     continue;
//                 }
//                 if (badTriangles[j].findEqualEdge(*edgePtrs[edgeIdx]) != nullptr){
//                     flagAdd = false;
//                     break;
//                 }
//             }
//             if (flagAdd){
//                 polygon.push_back(edgePtrs[edgeIdx]);
//             }
//         }
//     }

//     if (stage == 2){
//         auto cp = triangulation;
//         std::reverse(badIndexes.begin(), badIndexes.end());
//         for (auto badIdx: badIndexes){
//             cp.erase(cp.begin() + badIdx);
//         }

    
//         glColor3f(0.7f, 0.7f, 0.0f); 
//         debug_drawTriangs(cp);
//         return;
//     }
//     else{
//         std::reverse(badIndexes.begin(), badIndexes.end());
//         for (auto badIdx: badIndexes){
//             triangulation.erase(triangulation.begin() + badIdx);
//     }
//     }

//     for(auto& edge: polygon){
//         triangulation.push_back(NodesEdgesTriangles(*edge->nodePtrs[0], *edge->nodePtrs[1], point));
//     }

//     if (stage == 3){
//         glColor3f(0.7f, 0.7f, 0.0f); 
//         debug_drawTriangs(triangulation);
//         return;
//     }
// }

// std::vector<NodesEdgesTriangles> debug_triangulateBowyerWatson(std::vector<Point2D> inPoints, int stage)
// {
//     if (inPoints.size() <= 2){
//         return std::vector<NodesEdgesTriangles>();
//     }

//     std::vector<Node> points;
//     for (auto& inp: inPoints){
//         points.push_back(inp);
//     }

//     Edge* edgePtrs[3];

//     std::vector<NodesEdgesTriangles> triangulation;

//     if (points.size() <= 0){
//         return triangulation;
//     }

//     NodesEdgesTriangles superTriangle = createSuperTriangle(points);
//     triangulation.push_back(superTriangle);


//     for (int i = 0; i < points.size(); i++){
//         insertPointInTriangulation(points[i], triangulation);
//     } 
//     debug_insertPointInTriangulation(points[points.size()-1], triangulation, stage);

//     glColor3f(1.0f, 1.0f, 0.0f); 
    
//     for (int i = 0; i < points.size(); i++){
//         debug_drawPoint(points[i]);
//     } 
//     glColor3f(1.0f, 0.0f, 0.0f); 
//     debug_drawPoint(points[points.size()-1]);

//     glColor3f(1.0f, 1.0f, 1.0f); 
//     debug_drawEdges(triangulation);

//     glColor3f(0.0f, 1.0f, 1.0f); 
//     for (auto& tr: triangulation){
//         Node center;
//         float radius;
//         debug_calculate_circle(tr, center, radius);
//         debug_draw_circle(center, radius, 60);
//     }
//     // for (auto& point: points){
//     //     insertPointInTriangulation(point, triangulation);
//     // }

//     // delete because of superTriangle
//     std::vector<int> triangleIndexes;
//     int counter = 0;
//     for (auto& triangle: triangulation){
//         if (triangle.hasNode(superTriangle.node1) || triangle.hasNode(superTriangle.node2) || triangle.hasNode(superTriangle.node3)){
//             triangleIndexes.push_back(counter);
//         }
//         counter++;
//     }
//     std::reverse(triangleIndexes.begin(), triangleIndexes.end());
//     for (auto idx: triangleIndexes){
//             triangulation.erase(triangulation.begin() + idx);
//     }

    
//     //std::cout << triangulation.size() << " triangles in triangulation" << std::endl;
//     // for (auto& tr: triangulation){
//     //     std::cout << tr.node1.x << " " << tr.node1.y << std::endl;
//     //     std::cout << tr.node2.x << " " << tr.node2.y << std::endl;
//     //     std::cout << tr.node3.x << " " << tr.node3.y << std::endl;
//     // }

//     return triangulation;
// }

// // maps pixel coords to -1 to 1 (physical coords to viewport coords)
// Node debug_coordsToNormed(Node& node){

//     Node normedNode;
//     // 0 - min value
//     normedNode.x = -1.0 + 2.0 * (node.x - 0) / (1000 - 0);
//     normedNode.y =  2 * (1 - ((node.y - 0) / (800 - 0))) - 1;
//     return normedNode;
// }


// void debug_drawTriangs(std::vector<NodesEdgesTriangles> &trianglesVec)
// {

//     glBegin(GL_TRIANGLES);
//     for (auto & tr: trianglesVec){
//         auto normN1 = debug_coordsToNormed(tr.node1);
//         auto normN2 = debug_coordsToNormed(tr.node2);
//         auto normN3 = debug_coordsToNormed(tr.node3);
//         glVertex2d(normN1.x, normN1.y);
//         glVertex2d(normN2.x, normN2.y);
//         glVertex2d(normN3.x, normN3.y);
//     }
//     glEnd();
// }


// void debug_drawPoint(Node &point){
//     glBegin(GL_POINTS);


//     for (int i = -5; i < 6; i++){
//         for (int j = -5; j < 6; j++){
//             auto cp = point;
//             cp.x += i;
//             cp.y += j;
//             auto normN1 = debug_coordsToNormed(cp);
//             glVertex2d(normN1.x, normN1.y);
//         }
//     }

    
//     glEnd();
// }

// void debug_drawEdges(std::vector<NodesEdgesTriangles> &trianglesVec){
//     glBegin(GL_LINES);
//     for (auto& tr: trianglesVec){
//         auto normN1 = debug_coordsToNormed(tr.node1);
//         auto normN2 = debug_coordsToNormed(tr.node2);
//         auto normN3 = debug_coordsToNormed(tr.node3);
//         glVertex2d(normN1.x, normN1.y);
//         glVertex2d(normN2.x, normN2.y);
//         glVertex2d(normN2.x, normN2.y);
//         glVertex2d(normN3.x, normN3.y);
//         glVertex2d(normN3.x, normN3.y);
//         glVertex2d(normN1.x, normN1.y);
//    }
//    glEnd();
// }

// // Вычисление центра и радиуса описанной окружности для треугольника
// void debug_calculate_circle(const NodesEdgesTriangles& triangle, Node& center, float& radius) {

//     auto A = triangle.node1;
//     auto B = triangle.node2;
//     auto C = triangle.node3;
//     auto D = 2 * (A.x * (B.y - C.y) + B.x *(C.y - A.y) + C.x * (A.y - B.y));
//     center.x = ((A.x * A.x + A.y * A.y) * (B.y - C.y) +
//                 (B.x * B.x + B.y * B.y) * (C.y - A.y) +
//                 (C.x * C.x + C.y * C.y) * (A.y - B.y)) / D;
//     center.y = ((A.x * A.x + A.y * A.y) * (C.x - B.x) +
//                 (B.x * B.x + B.y * B.y) * (A.x - C.x) +
//                 (C.x * C.x + C.y * C.y) * (B.x - A.x)) / D;

//     //std::cout << "\npoints (" << A.x << " " << A.y << ") (" << B.x << " " << B.y << ") (" << C.x << " " << C.y << ")" << std::endl;
//     //std::cout << "center " << center.x << " " << center.y << " " << std::endl;

//     //float dx = A.x - center.x;
//     //std::cout << "delta A.x - center.x " << dx << std::endl;
//     //std::cout << "square " << dx * dx << std::endl;
//     //std::cout << "delta A.y - center.y " << A.y - center.y << std::endl;
//     //std::cout << "square " << (A.y - center.y) * (A.y - center.y) << std::endl;

//     radius = sqrt((A.x - center.x) * (A.x - center.x) + (A.y - center.y) * (A.y - center.y));
//     //std::cout << "radius " << radius << "\n" << std::endl;
// }

// void debug_draw_circle(const Node& center, float radius, int num_segments) {
//     glBegin(GL_LINE_LOOP);
//     for (int i = 0; i < num_segments; ++i) {
//         float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
//         float x = radius * std::cos(theta);
//         float y = radius * std::sin(theta);
//         Node n(center.x + x, center.y + y);
//         auto normN1 = debug_coordsToNormed(n);
//         glVertex2f(normN1.x, normN1.y);
//     }
//     glEnd();

// }

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

    nt1.x = minX - diffX * 0.1;
    nt1.y = minY - diffY;
    nt2.x = minX - diffX * 0.1;
    nt2.y = minY + diffY * 2;
    nt3.x = minX + diffX * 1.7;
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

    
    //std::cout << triangulation.size() << " triangles in triangulation" << std::endl;
    // for (auto& tr: triangulation){
    //     std::cout << tr.node1.x << " " << tr.node1.y << std::endl;
    //     std::cout << tr.node2.x << " " << tr.node2.y << std::endl;
    //     std::cout << tr.node3.x << " " << tr.node3.y << std::endl;
    // }

    return triangulation;
}

void insertPointInTriangulation(Node point, std::vector<NodesEdgesTriangles> &triangulation)
{
    Edge* edgePtrs[3] = {};

    std::vector<NodesEdgesTriangles> badTriangles;
    std::vector<int> badIndexes;
    int counter = 0;
    for (auto& triang: triangulation){
        if (!triang.delaunayCriteriaSatisfied(point)){
            badTriangles.push_back(triang);
            badIndexes.push_back(counter);
        }
        counter++;
    }
    std::vector<Edge*> polygon;
    for (int i = 0; i < badTriangles.size(); i++){
        edgePtrs[0] = &badTriangles[i].edge1;
        edgePtrs[1] = &badTriangles[i].edge2;
        edgePtrs[2] = &badTriangles[i].edge3;
        // foreach edge
        for (int edgeIdx = 0; edgeIdx < 3; edgeIdx++){
            bool flagAdd = true;
            for (int j = 0; j < badTriangles.size(); j++){
                if (i == j){
                    continue;
                }
                if (badTriangles[j].findEqualEdge(*edgePtrs[edgeIdx]) != nullptr){
                    flagAdd = false;
                    break;
                }
            }
            if (flagAdd){
                polygon.push_back(edgePtrs[edgeIdx]);
            }
        }
    }
    std::reverse(badIndexes.begin(), badIndexes.end());
    for (auto badIdx: badIndexes){
        triangulation.erase(triangulation.begin() + badIdx);
    }

    for(auto& edge: polygon){
        triangulation.push_back(NodesEdgesTriangles(*edge->nodePtrs[0], *edge->nodePtrs[1], point));
    }
}

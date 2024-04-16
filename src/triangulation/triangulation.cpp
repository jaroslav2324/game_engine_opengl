#include "triangulation.h"

void copyPtrToNeighbour(NodesEdgesTriangles& oldTriangle, NodesEdgesTriangles& newTriangle, Node& newNode){
        
    Edge* borderEdge = newTriangle.findEdgeWithoutNode(newNode);
    int emptyEdgeIdx = borderEdge->getFirstNullptrTriangleIdx();
    // get same edge from subdivided struct to copy pointer to neighbour triangle
    Edge* oldTriangleEdge = oldTriangle.findEqualEdge(*borderEdge);
    if (oldTriangleEdge->neighbourTriPtrs[0] != &oldTriangle.triangle){
        borderEdge->neighbourTriPtrs[emptyEdgeIdx] = oldTriangleEdge->neighbourTriPtrs[0];
    }
    if (oldTriangleEdge->neighbourTriPtrs[1] != &oldTriangle.triangle){
        borderEdge->neighbourTriPtrs[emptyEdgeIdx] = oldTriangleEdge->neighbourTriPtrs[0];
    }
}

void setNeighbourPtrsToNewTriangles(
    NodesEdgesTriangles& triangle, 
    NodesEdgesTriangles& trNeigh1,
    NodesEdgesTriangles& trNeigh2, 
    Node& insertedInTriangNode){

    Edge* ret1 = nullptr, *ret2 = nullptr;
    triangle.findTwoEdgesWithNode(ret1, ret2, insertedInTriangNode);
    // if ret1 is in newTr2 too
    if (trNeigh1.findEqualEdge(*ret1) != nullptr){
        // add pointer to neighbour triangles
        int insertIdx = ret1->getFirstNullptrTriangleIdx();
        ret1->neighbourTriPtrs[insertIdx] = &trNeigh1.triangle;
        insertIdx = ret2->getFirstNullptrTriangleIdx();
        ret2->neighbourTriPtrs[insertIdx] = &trNeigh2.triangle;
    }
    else if (trNeigh2.findEqualEdge(*ret1) != nullptr){
        int insertIdx = ret1->getFirstNullptrTriangleIdx();
        ret1->neighbourTriPtrs[insertIdx] = &trNeigh2.triangle;
        insertIdx = ret2->getFirstNullptrTriangleIdx();
        ret2->neighbourTriPtrs[insertIdx] = &trNeigh1.triangle;
    }
}

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

void subdivideTriangleInTriangulation(
    NodesEdgesTriangles &subdivideThis, 
    Node nodeInTriangle, 
    std::vector<NodesEdgesTriangles> &triangulation){

    NodesEdgesTriangles newTr1(subdivideThis.node1, subdivideThis.node2, nodeInTriangle);
    NodesEdgesTriangles newTr2(subdivideThis.node2, subdivideThis.node3, nodeInTriangle);
    NodesEdgesTriangles newTr3(subdivideThis.node3, subdivideThis.node1, nodeInTriangle);

    copyPtrToNeighbour(subdivideThis, newTr1, nodeInTriangle);
    copyPtrToNeighbour(subdivideThis, newTr2, nodeInTriangle);
    copyPtrToNeighbour(subdivideThis, newTr3, nodeInTriangle);

    setNeighbourPtrsToNewTriangles(newTr1, newTr2, newTr3, nodeInTriangle);
    setNeighbourPtrsToNewTriangles(newTr2, newTr1, newTr3, nodeInTriangle);
    setNeighbourPtrsToNewTriangles(newTr3, newTr1, newTr2, nodeInTriangle);

    // TODO
}

void triangulateBowyerWatson(std::vector<Node> points){

    std::vector<NodesEdgesTriangles> triangulation;
    NodesEdgesTriangles supreTriangle = createSuperTriangle(points);
    triangulation.push_back(supreTriangle);

    for (auto& point: points){
        std::vector<NodesEdgesTriangles*> badTriangles;
        std::vector<int> badIndexes;
        int counter = 0;
        for (auto& triang: triangulation){
            if (!triang.delaunayCriteriaSatisfied(point)){
                badTriangles.push_back(&triang);
                badIndexes.push_back(counter);
            }
            counter++;
        }
        std::vector<Edge> polygon;
        for (int i = 0; i < badTriangles.size(); i++){
            bool flagAdd = true;
            Edge addEdge;
            for (int j = 0; j < badTriangles.size(); j++){
                if (i == j)
                    continue;
                if (badTriangles[j]->findEqualEdge(badTriangles[i]->edge1)){
                    flagAdd = false;
                    addEdge = badTriangles[i]->edge1;
                    break;
                }
                if (badTriangles[j]->findEqualEdge(badTriangles[i]->edge2)){
                    flagAdd = false;
                    addEdge = badTriangles[i]->edge2;
                    break;
                }
                if (badTriangles[j]->findEqualEdge(badTriangles[i]->edge3)){
                    addEdge = badTriangles[i]->edge3;
                    flagAdd = false;
                    break;
                }
            }
            if (flagAdd){
                polygon.push_back(addEdge);
            }
        }
        std::reverse(badIndexes.begin(), badIndexes.end());
        for (auto badIdx: badIndexes){
            triangulation.erase(triangulation.begin() + badIdx);
        }

        for(auto& edge: polygon){
            triangulation.push_back(NodesEdgesTriangles(*edge.nodePtrs[0], *edge.nodePtrs[1], point));
        }
    }
    // delete because of superTriangle
    std::vector<int> triangleIndexes;
    int counter = 0;
    for (auto& triangle: triangulation){
        if (triangle.hasNode(supreTriangle.node1) || triangle.hasNode(supreTriangle.node2) || triangle.hasNode(supreTriangle.node3)){
            triangleIndexes.push_back(counter);
        }
        counter++;
    }
    std::reverse(triangleIndexes.begin(), triangleIndexes.end());
    for (auto idx: triangleIndexes){
            triangulation.erase(triangulation.begin() + idx);
    }
}
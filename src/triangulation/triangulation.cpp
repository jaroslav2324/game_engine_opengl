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
        // std::cout << triangle.node1.x << " " << triangle.node1.y << " " << triangle.node2.x << " " << triangle.node2.y << " " << triangle.node3.x << " " << triangle.node3.y << std::endl;
        if (triangle.hasNode(superTriangle.node1) || triangle.hasNode(superTriangle.node2) || triangle.hasNode(superTriangle.node3)){
            triangleIndexes.push_back(counter);
        }
        counter++;
    }
    // std::cout << std::endl;
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
        // std::cout << triang.node1.x << " " << triang.node1.y << " " << triang.node2.x << " " << triang.node2.y << " " << triang.node3.x << " " << triang.node3.y << std::endl;
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

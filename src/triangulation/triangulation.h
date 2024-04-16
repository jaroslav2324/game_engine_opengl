#include <vector>
#include "structures.h"
#include <algorithm>

// copy pointer to neighbour triangle from old triangle
void copyPtrToNeighbour(NodesEdgesTriangles& oldTriangle, NodesEdgesTriangles& newTriangle, Node& newNode);
// sets pointers to triangles in edges to neighbour triangles in subdivided old triangle
void setNeighbourPtrsToNewTriangles(NodesEdgesTriangles& triangle, NodesEdgesTriangles& trNeigh1,NodesEdgesTriangles& trNeigh2, Node& insertedInTriangNode);

NodesEdgesTriangles createSuperTriangle(std::vector<Node> points);

void triangulateBowyerWatson(std::vector<Node> points);

void subdivideTriangleInTriangulation(
    NodesEdgesTriangles& subdivideThis,
    Node nodeInTriangle,
    std::vector<NodesEdgesTriangles>& triangulation);


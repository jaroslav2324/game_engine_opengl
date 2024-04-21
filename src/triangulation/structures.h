#pragma once

#include <iostream>
#include <cmath>


struct Node;
struct Edge;
struct Triangle;

typedef struct Node
{
    Node(): x(0), y(0){};
    Node(float x, float y): x(x), y(y){};
    bool operator==(Node& node);
    bool operator!=(Node& node);

    float x;
    float y;

} Node;


typedef struct Edge
{
    bool operator==(Edge& edge);
    int getFirstNullptrTriangleIdx();

    Node* nodePtrs[2];
    Triangle* neighbourTriPtrs[2];

} Edge;

typedef struct Triangle{
    Edge* edgePtrs[3];
} Triangle;

// represents triangle, three edges and three nodes
typedef struct NodesEdgesTriangles
{
    NodesEdgesTriangles(Node n1, Node n2, Node n3);
    NodesEdgesTriangles(const NodesEdgesTriangles& copyThis);
    Node node1, node2, node3;
    Edge edge1, edge2, edge3;
    Triangle triangle;

    bool delaunayCriteriaSatisfied(Node checkNode);
    bool nodeInTriangle(Node checkNode);
    Edge* findEdgeWithoutNode(Node& node);
    Edge* findEqualEdge(Edge& edge);
    void findTwoEdgesWithNode(Edge* returnEdge1, Edge* returnEdge2, Node& node);
    bool hasNode(Node& node);
    bool hasEdge(Edge& edge);

    private:
    void initInnerPointers();

} NodesEdgesTriangles;

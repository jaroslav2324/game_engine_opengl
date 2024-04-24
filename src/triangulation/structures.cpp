#include "structures.h"

void NodesEdgesTriangles::initInnerPointers(){
    
    edge1.nodePtrs[0] = &node1;
    edge1.nodePtrs[1] = &node2;
    edge2.nodePtrs[0] = &node2;
    edge2.nodePtrs[1] = &node3;
    edge3.nodePtrs[0] = &node3;
    edge3.nodePtrs[1] = &node1;

    edge1.neighbourTriPtrs[0] = &triangle;
    edge1.neighbourTriPtrs[1] = nullptr;
    edge2.neighbourTriPtrs[0] = &triangle;
    edge2.neighbourTriPtrs[1] = nullptr;
    edge3.neighbourTriPtrs[0] = &triangle;
    edge3.neighbourTriPtrs[1] = nullptr;

    triangle.edgePtrs[0] = &edge1;
    triangle.edgePtrs[1] = &edge2;
    triangle.edgePtrs[2] = &edge3;
}


NodesEdgesTriangles::NodesEdgesTriangles(Node n1, Node n2, Node n3){
    
    node1 = n1;
    node2 = n2;
    node3 = n3;
    initInnerPointers();
}

NodesEdgesTriangles::NodesEdgesTriangles(const NodesEdgesTriangles &copyThis){

    //std::cout << "NodesEdgesTriangles copy constructor called" << std::endl;

    node1 = copyThis.node1;
    node2 = copyThis.node2;
    node3 = copyThis.node3;

    initInnerPointers();
}

bool NodesEdgesTriangles::delaunayCriteriaSatisfied(Node checkNode){

    // TODO reduce overflow chance

    auto& A = node1;
    auto& B = node2;
    auto& C = node3;
    auto D = 2 * (A.x * (B.y - C.y) + B.x *(C.y - A.y) + C.x * (A.y - B.y));
    Node center;
    center.x = ((A.x * A.x + A.y * A.y) * (B.y - C.y) +
                (B.x * B.x + B.y * B.y) * (C.y - A.y) +
                (C.x * C.x + C.y * C.y) * (A.y - B.y)) / D;
    center.y = ((A.x * A.x + A.y * A.y) * (C.x - B.x) +
                (B.x * B.x + B.y * B.y) * (A.x - C.x) +
                (C.x * C.x + C.y * C.y) * (B.x - A.x)) / D;

    float radius = sqrt((A.x - center.x) * (A.x - center.x) + (A.y - center.y) * (A.y - center.y));

    float distanceSquared = (checkNode.x - center.x) * (checkNode.x - center.x) + (checkNode.y - center.y) * (checkNode.y - center.y);

    float epsilon = 1.0;

    if (std::abs(distanceSquared - radius * radius ) < epsilon)
        return false;

    if (distanceSquared < radius * radius)
        return false;

    return true;
}

bool NodesEdgesTriangles::nodeInTriangle(Node checkNode){

    float shiftX = -node1.x;
    float shiftY = -node1.y;

    float n2x = node2.x + shiftX;
    float n2y = node2.y + shiftY;
    float n3x = node3.x + shiftX;
    float n3y = node3.y + shiftY; 
    float checkX = checkNode.x + shiftX;
    float checkY = checkNode.y + shiftY;

    float m = (checkX * n2y - n2x * checkY) / (n3x * n2y - n2x * n3y);
    if (m >= 0 && m <= 1){
        float l = (checkX - m * n3x) / n2x;
        if (l >= 0 && (m + l) <= 1){
            return true;
        }
    }
    return false;
}

Edge *NodesEdgesTriangles::findEdgeWithoutNode(Node &node)
{
    if (*edge1.nodePtrs[0] != node && *edge1.nodePtrs[1] != node )
        return &edge1;
    if (*edge2.nodePtrs[0] != node && *edge2.nodePtrs[1] != node )
        return &edge2;
    if (*edge3.nodePtrs[0] != node && *edge3.nodePtrs[1] != node )
        return &edge3;
    return nullptr;
}

Edge *NodesEdgesTriangles::findEqualEdge(Edge &edge)
{
    if (edge == edge1)
        return &edge1;
    if (edge == edge2)
        return &edge2;
    if (edge == edge3)
        return &edge3;

    return nullptr;
}

void NodesEdgesTriangles::findTwoEdgesWithNode(Edge *returnEdge1, Edge *returnEdge2, Node& node){
    Edge* withoutNode = findEdgeWithoutNode(node);
    if (&edge1 == withoutNode){
        returnEdge1 = &edge2;
        returnEdge2 = &edge3;
    }
    else if (&edge2 == withoutNode){
        returnEdge1 = &edge3;
        returnEdge2 = &edge1;
    }
    else if (&edge3 == withoutNode){
        returnEdge1 = &edge1;
        returnEdge2 = &edge2;
    }
    else{
        returnEdge1 = nullptr;
        returnEdge2 = nullptr;
    }
}

bool NodesEdgesTriangles::hasNode(Node &node)
{
    if (node1 == node || node2 == node || node3 == node)
        return true;
    return false;
}

bool NodesEdgesTriangles::hasEdge(Edge &edge)
{
     if (edge == edge1 || edge == edge2 || edge == edge3)
        return true;
    return false;
}

bool Node::operator==(Node &node)
{
    float epsilon = 1.0e-3;
    return (std::abs(x - node.x) < epsilon) && (std::abs(y - node.y) < epsilon);
}

bool Node::operator!=(Node &node)
{
    return !operator==(node);
}

bool Edge::operator==(Edge &edge)
{
    if ((*nodePtrs[0] == *edge.nodePtrs[0] && *nodePtrs[1] == *edge.nodePtrs[1])
    || (*nodePtrs[1] == *edge.nodePtrs[0] && *nodePtrs[0] == *edge.nodePtrs[1]))
        return true;
    return false;
}

int Edge::getFirstNullptrTriangleIdx()
{
    for (int i = 0; i < 2; i++){
        if (neighbourTriPtrs[i] == nullptr)
            return i;
    }
    return -1;
}

EdgeWithNodes::EdgeWithNodes(Edge &edge){
    node1 = *edge.nodePtrs[0];
    node2 = *edge.nodePtrs[1];
}

bool EdgeWithNodes::operator==(EdgeWithNodes &edge)
{
    if (((node1 == edge.node1) && (node2 == edge.node2)) || 
    ((node1 == edge.node2) && (node2 == edge.node1)))
        return true;
    return false;
}

NodesEdgesTriangles& NodesEdgesTriangles::operator=(const NodesEdgesTriangles& other) {

// std::cout << "NodesEdgesTriangles operator= called" << std::endl;

    if (this != &other) { 

        node1 = other.node1;
        node2 = other.node2;
        node3 = other.node3;
        initInnerPointers();
        isBad = other.isBad;
    }
    return *this;
}
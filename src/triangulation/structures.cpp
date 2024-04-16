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
    initInnerPointers();
    node1 = n1;
    node2 = n2;
    node3 = n3;
}

// check using modified sum of opposite angles
bool NodesEdgesTriangles::delaunayCriteriaSatisfied(Node checkNode){

    // cos a
    float sa = (checkNode.x - node1.x) * (checkNode.x - node3.x) + (checkNode.y - node1.y) * (checkNode.y - node3.y);
    // cos b
    float sb = (node2.x - node1.x) * (node2.x - node3.x) + (node2.y - node1.y) * (node2.y - node3.y);

    if (sa < 0 && sb < 0){
        return false;
    }

    if (sa >= 0 && sb >= 0){
        return true;
    }

    float fullCalculation = (((checkNode.x - node1.x) * (checkNode.y - node3.y) - (checkNode.x - node3.x) * (checkNode.y - node1.y)) * sb) 
                            + 
                            (sa * ((node2.x - node1.x) * (node2.y - node3.y) - (node2.x - node3.x) * (node2.y - node1.y)));

    if (fullCalculation >= 0){
        return true;
    }
    else{
        return false;
    }


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
    if (edge == edge2)
        return &edge2;

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

bool Node::operator==(Node &node)
{
    if (x == node.x && y == node.y)
        return true;
    return false;
}

bool Node::operator!=(Node &node)
{
    if (x == node.x && y == node.y)
        return false;
    return true;
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
}

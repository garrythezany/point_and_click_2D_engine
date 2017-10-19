#include "Pathfinder.h"

void BRO::Node::addAdjacent(const Node &node) {
    adjacencyList.push_back(node);
}

void BRO::Polygon::assign(sf::ConvexShape &_shape, BRO::Node &_node) {
    shape = _shape;
    node = _node;
}

void BRO::NavMesh::addPoly(BRO::Polygon &poly) {
    polyList.push_back(poly);
}

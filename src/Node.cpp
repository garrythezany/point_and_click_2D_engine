#include "Node.h"

void BRO::Node::addAdjacent(const Node &node) {
    adjacencyList.push_back(node);
}
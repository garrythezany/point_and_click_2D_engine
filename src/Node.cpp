//
// Created by Roman Hock on 19.10.17.
//

#include "Node.h"

void BRO::Node::addAdjacent(const Node &node) {
    adjacencyList.push_back(node);
}
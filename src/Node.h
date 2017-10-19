//
// Created by Roman Hock on 19.10.17.
//

#ifndef SFML_NODE_H
#define SFML_NODE_H

#include <vector>

namespace BRO{
    class Node {
    public:
        std::vector<Node> adjacencyList;

        void addAdjacent(const Node &node);
    };
}


#endif //SFML_NODE_H

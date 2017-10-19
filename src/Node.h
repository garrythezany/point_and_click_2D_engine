#ifndef PNR_Engine_NODE_H
#define PNR_Engine_NODE_H

#include <vector>

namespace BRO{
    class Node {
    public:
        std::vector<Node> adjacencyList;

        void addAdjacent(const Node &node);
    };
}

#endif //PNR_Engine_NODE_H

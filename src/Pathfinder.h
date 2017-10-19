#ifndef PNC_ENGINE_PATHFINDER_H
#define PNC_ENGINE_PATHFINDER_H

#include <vector>
#include <SFML/Graphics.hpp>

namespace BRO{

    //-----------------
    // GRAPH-NODES
    //-----------------
    class Node {
    public:
        std::vector<Node> adjacencyList;

        void addAdjacent(const Node &node);
    };

    //-------------------------
    // POLYGONS (shape + node)
    //-------------------------
    class Polygon {
    public:
        sf::ConvexShape shape;
        BRO::Node node;

        void assign(sf::ConvexShape &_shape, BRO::Node &_node);
    };

    //-----------------
    // NAV-MESH
    //-----------------
    class NavMesh {
    public:
        std::vector<BRO::Polygon> polyList;

        void addPoly(BRO::Polygon &poly);
    };
}

#endif //PNC_ENGINE_PATHFINDER_H

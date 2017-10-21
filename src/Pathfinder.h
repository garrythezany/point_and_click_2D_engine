#ifndef PNC_ENGINE_PATHFINDER_H
#define PNC_ENGINE_PATHFINDER_H

#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Cursor.h"

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
        std::vector<sf::ConvexShape> shapeList;

        void addPoly(BRO::Polygon &poly);
        void addShape(sf::ConvexShape &shape);
    };

    //-----------------
    // LINES etc
    //-----------------
    class Pathfinder {
    public:
        bool CCW(const std::vector<sf::Vector2f>& points);

        // vector of (2) lines. line is a vector of (2) vector2fs (the points of the line).
        // i.e. { { line1.x, line.y }, { line2.x, line2.y } }
        bool doLinesIntersect(const std::vector<std::vector<sf::Vector2f>>& lines);

        bool isPointInsidePolygon(const sf::Vector2f& point, const std::vector<sf::Vector2f>& polygonVertices);

        bool isPointInsidePolygon(const sf::Vector2f& point, const std::vector<sf::Vector2f>& polygonVertices, const sf::FloatRect& boundingBox);

        sf::FloatRect boundingBox(const std::vector<sf::Vector2f>& vertices);

        void validPolygon(BRO::NavMesh &navMesh, BRO::Player &player, BRO::Cursor &cursor);
    };
}

#endif //PNC_ENGINE_PATHFINDER_H

//
// Created by Roman Hock on 19.10.17.
//

#ifndef SFML_POLYGON_H
#define SFML_POLYGON_H

#include <SFML/Graphics.hpp>
#include "Node.h"

namespace BRO{
    class Polygon {
    public:
        sf::ConvexShape shape;
        BRO::Node node;

        void assign(sf::ConvexShape &_shape, BRO::Node &_node);
    };
}

#endif //SFML_POLYGON_H

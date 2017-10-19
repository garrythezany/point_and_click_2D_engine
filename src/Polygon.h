#ifndef PNR_Engine_POLYGON_H
#define PNR_Engine_POLYGON_H

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

#endif //PNR_Engine_POLYGON_H

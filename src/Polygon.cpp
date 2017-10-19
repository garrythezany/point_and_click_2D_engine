//
// Created by Roman Hock on 19.10.17.
//

#include "Polygon.h"

void BRO::Polygon::assign(sf::ConvexShape &_shape, BRO::Node &_node) {
    shape = _shape;
    node = _node;
}
//
// Created by Roman Hock on 19.10.17.
//

#ifndef SFML_NAVMESH_H
#define SFML_NAVMESH_H

#include "Polygon.h"

namespace BRO{
    class NavMesh {
    public:
        std::vector<BRO::Polygon> polyList;

        void addPoly(BRO::Polygon &poly);
    };

}

#endif //SFML_NAVMESH_H

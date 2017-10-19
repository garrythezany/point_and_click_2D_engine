#ifndef PNR_Engine_NAVMESH_H
#define PNR_Engine_NAVMESH_H

#include "Polygon.h"

namespace BRO{
    class NavMesh {
    public:
        std::vector<BRO::Polygon> polyList;

        void addPoly(BRO::Polygon &poly);
    };

}

#endif //PNR_Engine_NAVMESH_H

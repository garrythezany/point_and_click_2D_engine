#ifndef PNR_Engine_WORLD_H
#define PNR_Engine_WORLD_H

#include <vector>
#include "Room.h"
#include "Node.h"
#include "Polygon.h"
#include "NavMesh.h"

namespace BRO{
    class World {
    public:
        std::vector<BRO::Room> world;

        void initArcadeRoom(unsigned int &resMultiplier);
        void initStudioRoom(unsigned int &resMultiplier);

        void initWorld(unsigned int &resMultiplier);
    };
}

#endif //PNR_Engine_WORLD_H

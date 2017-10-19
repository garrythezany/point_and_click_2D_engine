//
// Created by Roman Hock on 19.10.17.
//

#ifndef SFML_WORLD_H
#define SFML_WORLD_H

#include <vector>
#include "Room.h"
#include "Node.h"
#include "Polygon.h"
#include "NavMesh.h"

namespace BRO{
    class World {
    public:
        std::vector<BRO::Room> world;

        void initArcadeRoom(int resMultiplier);
        void initStudioRoom(int resMultiplier);

        void initWorld(int resMultiplier);
    };
}




#endif //SFML_WORLD_H

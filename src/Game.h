//
// Created by Roman Hock on 19.10.17.
//

#ifndef SFML_GAME_H
#define SFML_GAME_H

#include "Node.h"
#include "Polygon.h"
#include "NavMesh.h"
#include "Cursor.h"
#include "Player.h"

namespace BRO{
    class Game {
    public:
        unsigned int resMultiplier = 6;
        float resMultiplierF = resMultiplier;

        sf::RenderWindow window;

        void setResMultiplier(unsigned int multiplier);
    };

}

#endif //SFML_GAME_H

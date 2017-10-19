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
#include "Room.h"
#include "Item.h"
//#include "World.h"

namespace BRO{
    class Game {
    public:
        unsigned int resMultiplier = 6;
        float resMultiplierF = resMultiplier;

        sf::RenderWindow window;

        void setResMultiplier(unsigned int multiplier);


    };

    enum class GameStates{
        STATE_START = 1,
        STATE_MENU,
        STATE_OPTIONS,
        STATE_PLAYING
    };

}

#endif //SFML_GAME_H

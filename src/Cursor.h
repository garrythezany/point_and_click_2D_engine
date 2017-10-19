//
// Created by Roman Hock on 19.10.17.
//

#ifndef SFML_CURSOR_H
#define SFML_CURSOR_H

#include <SFML/Graphics.hpp>
#include "Game.h"

namespace BRO{
    class Cursor {
    private:
        sf::Texture texture;
    public:
        sf::Sprite sprite;

        Cursor();

        void setScale(int _resMultiplier);

        void update(sf::Vector2f coordinates);

    };
}


#endif //SFML_CURSOR_H

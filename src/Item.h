//
// Created by Roman Hock on 19.10.17.
//

#ifndef SFML_ITEM_H
#define SFML_ITEM_H

#include <SFML/Graphics.hpp>

namespace BRO{
    class Item{
    private:
        sf::Texture texture;

    public:
        sf::Sprite sprite;

        Item(const std::string filePath, float positionX, float positionY, int resMultiplier);
    };
}


#endif //SFML_ITEM_H

#ifndef PNR_Engine_ITEM_H
#define PNR_Engine_ITEM_H

#include <SFML/Graphics.hpp>

namespace BRO{
    class Item{
    private:
        sf::Texture texture;

    public:
        sf::Sprite sprite;

        Item(const std::string filePath, float positionX, float positionY, unsigned int &resMultiplier);
    };
}

#endif //PNR_Engine_ITEM_H
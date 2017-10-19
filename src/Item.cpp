//
// Created by Roman Hock on 19.10.17.
//

#include "Item.h"

BRO::Item::Item(const std::string filePath, float positionX, float positionY, int resMultiplier){
    texture.loadFromFile(filePath);
    sprite.setTexture(texture);
    sprite.scale(resMultiplier, resMultiplier);
    sprite.setPosition(positionX, positionY);
}
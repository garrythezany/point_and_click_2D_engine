//
// Created by Roman Hock on 19.10.17.
//

#include "Cursor.h"
#include "Game.h"

BRO::Cursor::Cursor(){
    texture.loadFromFile("cursor.png");
    sprite.setTexture(texture);
    sprite.setOrigin(8, 8);
    sprite.setPosition(400, 400);
}

void BRO::Cursor::setScale(int _resMultiplier){
    sprite.setScale(_resMultiplier, _resMultiplier);
}

void BRO::Cursor::update(sf::Vector2f coordinates){
    sprite.setPosition(coordinates);
}
//
// Created by Roman Hock on 10.10.17.
//

#include "Cursor.h"

sf::Texture cursorTexture;
sf::Sprite cursorSprite;

// Constructor
Cursor::Cursor(){
    cursorTexture.loadFromFile("cursor.png");
    cursorSprite.setTexture(cursorTexture);
    cursorSprite.setOrigin(8, 8);
    cursorSprite.scale(resMultiplier, resMultiplier);
    cursorSprite.setPosition(400, 400);
}
Cursor::void update(){
    cursorSprite.setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
}
//
// Created by Bastian Wegge on 10.10.17.
//

#include <SFML/Graphics.hpp>

class Cursor {
public:
    sf::Texture texture;
    sf::Sprite sprite;

    // Constructor
    Cursor() {
        texture.loadFromFile("cursor.png");
        sprite.setTexture(texture);
        sprite.setOrigin(8, 8);
        sprite.scale(2, 2);
        sprite.setPosition(400, 400);
    }
    void update(sf::RenderWindow& _window){
        sprite.setPosition(_window.mapPixelToCoords(sf::Mouse::getPosition(_window)));
    }
};

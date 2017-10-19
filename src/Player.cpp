//
// Created by Roman Hock on 19.10.17.
//

#include "Player.h"

//---------------------------
// Constructor
//---------------------------
BRO::Player::Player(const std::string &filePath, int resMultiplier){
    mask.left = 0;
    mask.top = 0;
    mask.width = 64;
    mask.height = 80;
    texture.loadFromFile(filePath);
    sprite.setTexture(texture);
    sprite.setTextureRect(mask);
    sprite.setOrigin(32, 77);

    // scale sprite based on y-axis,
    // where y = 100 * game.resMultiplier results in a scale of 1 * game.resMultiplier
    sprite.setScale(0.01f * (sprite.getPosition().y / resMultiplier) * resMultiplier,
                    0.01f * (sprite.getPosition().y / resMultiplier) * resMultiplier);

    // The target, that the player moves towards
    moveTarget = sf::Vector2f(sprite.getPosition());
}

//------------------------------------
// Sprite Animation System
//------------------------------------
void BRO::Player:: iterateSprite(int top, int startLeft, int maxLeft, int incrementLeft, float speed){
    mask.top = top;
    if (clock.getElapsedTime().asSeconds() > speed){
        if (mask.left >= maxLeft) {
            mask.left = startLeft;
        }
        else {
            mask.left += incrementLeft;
        }
        sprite.setTextureRect(mask);
        clock.restart();
    }
}

//---------------------------
// set Target
//---------------------------
void BRO::Player:: setTarget(sf::Vector2f coordinates){
    moveTarget = sf::Vector2f(coordinates);
}

//----------------------------------------------
// walk-animations + sprite movement
//----------------------------------------------
void BRO::Player:: walk(int resMultiplier, float resMultiplierF){
    sf::Vector2f direction = sf::Vector2f(moveTarget.x, moveTarget.y) - sprite.getPosition();
    float magnitude = sqrt((direction.x * direction.x) + (direction.y * direction.y));
    sf::Vector2f unitVector((direction.x * 1.3f) / magnitude, direction.y / (magnitude * 1.8f));

    // overall player-speed
    sprite.move(unitVector * 0.8f * resMultiplierF);

    // scale player based on y-axis
    sprite.setScale((0.01f * (sprite.getPosition().y / resMultiplier) * 0.999f) * resMultiplier,
                    (0.01f * (sprite.getPosition().y / resMultiplier) * 0.999f) * resMultiplier);

    // direction stuff
    float positiveDirectionX;
    float positiveDirectionY;

    if (direction.x < 0){
        positiveDirectionX = - direction.x;
    } else {
        positiveDirectionX = direction.x;
    }
    if (direction.y < 0){
        positiveDirectionY = - direction.y;
    } else {
        positiveDirectionY = direction.y;
    }

    // walk left
    if (direction.x < 0 && positiveDirectionX > positiveDirectionY){
        iterateSprite(80, 0, 192, 64, .08f);
    }
        // walk right
    else if (direction.x > 0 && positiveDirectionX > positiveDirectionY){
        iterateSprite(160, 0, 192, 64, .08f);
    }
        // walk front
    else if (positiveDirectionX < positiveDirectionY && direction.y > 0){
        iterateSprite(240, 0, 320, 64, .08f);
    }
        // walk back
    else if (positiveDirectionX < positiveDirectionY && direction.y < 0){
        iterateSprite(320, 0, 320, 64, .08f);
    }
}

//---------------------------
// idle animation
//---------------------------
void BRO::Player::idle(){
    iterateSprite(0, 0, 448, 64, .2f);
}

//------------------------------------
// handling all animations
//------------------------------------
void BRO::Player:: animate(int resMultiplier, float resMultiplierF){
    if (round(moveTarget.x) != round(sprite.getPosition().x) && round(moveTarget.y) != round(sprite.getPosition().y)){
        walk(resMultiplier, resMultiplierF);
    } else {
        idle();
    }
}

//-----------------------------
// get X-Coordinate
//-----------------------------
int BRO::Player::getPositionX(){
    float posF = sprite.getPosition().x;
    int posI = floor((posF * 100.0) + 0.5) / 100;
    return posI;
}
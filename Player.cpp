//
// Created by Bastian Wegge on 10.10.17.
//
#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

using namespace std;

class Player{
private:
    sf::Texture playerTexture;

    void iterateSprite(int top, int startLeft, int maxLeft, int incrementLeft, float speed){
        playerMask.top = top;
        if (clock.getElapsedTime().asSeconds() > speed){
            if (playerMask.left >= maxLeft) {
                playerMask.left = startLeft;
            }
            else {
                playerMask.left += incrementLeft;
            }
            playerSprite.setTextureRect(playerMask);
            clock.restart();
        }
    }

public:
    // init Objects
    sf::IntRect playerMask;
    sf::Sprite playerSprite;
    sf::Clock clock;
    sf::Vector2f moveTarget;

    // Constructor
    explicit Player(const string &filePath){
        playerMask.left = 0;
        playerMask.top = 0;
        playerMask.width = 64;
        playerMask.height = 80;
        playerTexture.loadFromFile(filePath);
        playerSprite.setTexture(playerTexture);
        playerSprite.setTextureRect(playerMask);
        playerSprite.setOrigin(32, 77);
        playerSprite.setPosition(200 * 2, 115 * 2);
        playerSprite.scale(2, 2);
        moveTarget = sf::Vector2f(playerSprite.getPosition());
    }

    void setTarget(sf::RenderWindow& _window){
        moveTarget = sf::Vector2f(_window.mapPixelToCoords(sf::Mouse::getPosition(_window)));
    }

    void walk(){
        sf::Vector2f direction = sf::Vector2f(moveTarget.x, moveTarget.y) - playerSprite.getPosition();
        float magnitude = sqrt((direction.x * direction.x) + (direction.y * direction.y));
        sf::Vector2f unitVector((direction.x * 1.3f) / magnitude, direction.y / (magnitude * 1.8f));

        // overall player-speed
        playerSprite.move(unitVector * 0.8f * 2.0f);

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

    void idle(){
        iterateSprite(0, 0, 448, 64, .2f);
    }

    void animate(){
        if (round(moveTarget.x) != round(playerSprite.getPosition().x) && round(moveTarget.y) != round(playerSprite.getPosition().y)){
            walk();
        } else {
            idle();
        }
    }
    int getPositionX(){
        float posF = playerSprite.getPosition().x;
        int posI = floor((posF * 100.0) + 0.5) / 100;
        return posI;
    }
};
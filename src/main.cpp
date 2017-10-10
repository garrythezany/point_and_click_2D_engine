#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <Cursor.h>
#include <config.cpp>

using namespace std;



// Classes
namespace BRO {

    class Player{
    private:
        sf::Texture playerTexture;

        // TODO - fix function - sprite disappears on click
        void iterateSprite(int top, int startLeft, int maxLeft, int incrementLeft, float speed){
            playerMask.top = top;
            if (clock.getElapsedTime().asSeconds() > speed){
                if (playerMask.left == maxLeft) {
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
            playerSprite.setPosition(200 * resMultiplier, 115 * resMultiplier);
            playerSprite.scale(resMultiplier, resMultiplier);
            moveTarget = sf::Vector2f(playerSprite.getPosition());
        }

        void setTarget(){
            moveTarget = sf::Vector2f(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
        }

        void idle(){
            // TODO - use iterateSprite()
            playerMask.top = 0;
            if (clock.getElapsedTime().asSeconds() > 0.2f){
                if (playerMask.left == 448) {
                    playerMask.left = 0;
                }
                else {
                    playerMask.left += 64;
                }
                playerSprite.setTextureRect(playerMask);
                clock.restart();
            }
        }
        void walk(){
            sf::Vector2f direction = sf::Vector2f(moveTarget.x, moveTarget.y) - playerSprite.getPosition();
            float magnitude = sqrt((direction.x * direction.x) + (direction.y * direction.y));
            sf::Vector2f unitVector((direction.x * 1.3f) / magnitude, direction.y / (magnitude * 1.8f));

            // overall player-speed
            playerSprite.move(unitVector * 0.8f * resMultiplierF);

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
                // TODO - use iterateSprite()
                playerMask.top = 80;
                if (clock.getElapsedTime().asSeconds() > 0.08f){
                    if (playerMask.left >= 192) {
                        playerMask.left = 0;
                    }
                    else {
                        playerMask.left += 64;
                    }
                    playerSprite.setTextureRect(playerMask);
                    clock.restart();
                }
            }
                // walk right
            else if (direction.x > 0 && positiveDirectionX > positiveDirectionY){
                // TODO - use iterateSprite()
                playerMask.top = 160;
                if (clock.getElapsedTime().asSeconds() > 0.08f) {
                    if (playerMask.left >= 192) {
                        playerMask.left = 0;
                    } else {
                        playerMask.left += 64;
                    }
                    playerSprite.setTextureRect(playerMask);
                    clock.restart();
                }
            }
                // walk front
            else if (positiveDirectionX < positiveDirectionY && direction.y > 0){
                // TODO - use iterateSprite()
                playerMask.top = 240;
                if (clock.getElapsedTime().asSeconds() > 0.08f) {
                    if (playerMask.left >= 320) {
                        playerMask.left = 0;
                    } else {
                        playerMask.left += 64;
                    }
                    playerSprite.setTextureRect(playerMask);
                    clock.restart();
                }
            }
                // walk back
            else if (positiveDirectionX < positiveDirectionY && direction.y < 0){
                // TODO - use iterateSprite()
                playerMask.top = 320;
                if (clock.getElapsedTime().asSeconds() > 0.08f) {
                    if (playerMask.left >= 320) {
                        playerMask.left = 0;
                    } else {
                        playerMask.left += 64;
                    }
                    playerSprite.setTextureRect(playerMask);
                    clock.restart();
                }
            }
        };
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

    class Room{
    private:
        sf::Texture roomTexture;
        bool isScrollable;

    public:
        sf::View view;
        sf::FloatRect viewMask;
        sf::Sprite roomSprite;
        float moveTargetX;
        // constructor
        explicit Room(const string &filePath){
            viewMask.left = 0;
            viewMask.top = 0;
            viewMask.width = 320 * resMultiplier;
            viewMask.height = 200 * resMultiplier;
            view.reset(viewMask);
            roomTexture.loadFromFile(filePath);
            roomSprite.setTexture(roomTexture);
            roomSprite.scale(resMultiplier, resMultiplier);
            //cout << "size is " << roomTexture.getSize().x << endl;
            if (roomTexture.getSize().x != viewMask.width || roomTexture.getSize().y != viewMask.height){
                isScrollable = true;
            } else {
                isScrollable = false;
            }
        }

        void scrollHorizontal(float playerPositionX){
            if (isScrollable){
                if (playerPositionX > viewMask.width + viewMask.left - 100 * resMultiplier && roomTexture.getSize().x * resMultiplier > viewMask.width + viewMask.left){
                    viewMask.left += 1 * resMultiplier;
                } else if (playerPositionX < viewMask.left + 100 * resMultiplier && viewMask.left > 0){
                    viewMask.left -= 1 * resMultiplier;
                }
            }
        }
    };
}

int main() {
    sf::Event event;
    window.create(sf::VideoMode(320 * resMultiplier, 200 * resMultiplier, 32),"Bronko Engine", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(90);
    window.setMouseCursorVisible(false);

    // Frame Clock
    sf::Clock clock;
    sf::Clock moveClock;

    BRO::Cursor cursor;
    //BRO::Room bedroom("bedroom.png");
    //BRO::Room shop("shop.png");
    BRO::Room arcade("arcade.png");
    BRO::Player player("sprite_full.png");

    BRO::Room currentRoom = arcade;
    BRO::Player currentPlayer = player;

    while(window.isOpen()){
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }

        currentPlayer.animate();
        cursor.update();

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
            sf::Mouse::getPosition(window).x <= window.getSize().x &&
            sf::Mouse::getPosition(window).y <= window.getSize().y &&
            sf::Mouse::getPosition(window).x >= 0 &&
            sf::Mouse::getPosition(window).y >= 0)
        {
            currentPlayer.setTarget();
        }

        window.setView(currentRoom.view);

        currentRoom.scrollHorizontal(currentPlayer.playerSprite.getPosition().x);
        currentRoom.view.reset(currentRoom.viewMask);

        window.clear(sf::Color::Black);

        //window.draw(bedroom.roomSprite);
        //window.draw(shop.roomSprite);
        window.draw(currentRoom.roomSprite);
        window.draw(currentPlayer.playerSprite);
        window.draw(cursor.cursorSprite);

        window.display();
    }
    return 0;
}
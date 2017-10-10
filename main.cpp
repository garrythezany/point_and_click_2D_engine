#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

using namespace std;

sf::RenderWindow window;


namespace BRO {
    class Cursor{
        private:
            sf::Texture cursorTexture;

        public:
            sf::Sprite cursorSprite;

            // Constructor
            Cursor(){
                cursorTexture.loadFromFile("cursor.png");
                cursorSprite.setTexture(cursorTexture);
                cursorSprite.setOrigin(32, 32);
                cursorSprite.setPosition(400, 400);
            }
            void update(){
                cursorSprite.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
            }
    };

    class Player{
        public:
            // init Objects
            sf::Texture playerTexture;
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
                playerSprite.setPosition(1300, 610);
                playerSprite.scale(5.9f, 5.9f);
                moveTarget = sf::Vector2f(playerSprite.getPosition());
            }

            void setTarget(){
                moveTarget = sf::Vector2f(sf::Mouse::getPosition(window));
            }

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
                playerSprite.move(unitVector * 4.f);

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
    };

    class Room{
        private:
            sf::Texture roomTexture;

        public:
            sf::View view;
            sf::Sprite roomSprite;
            // constructor
            explicit Room(const string &filePath){
                view.reset(sf::FloatRect(0, 0, 320*5, 200*5));
                roomTexture.loadFromFile(filePath);
                roomSprite.setTexture(roomTexture);
                roomSprite.scale(5.f, 5.f);
            }

            // TODO: scroll view for rooms that are bigger than it
            void moveView(){}
    };
}

int main() {
    sf::Event event;
    window.create(sf::VideoMode(1600,1000,32),"Bronko Engine");
    window.setFramerateLimit(90);
    window.setMouseCursorVisible(false);

    // Frame Clock
    sf::Clock clock;
    sf::Clock moveClock;

    BRO::Cursor cursor;
    BRO::Room bedroom("bedroom.png");
    BRO::Room shop("shop.png");
    BRO::Room arcade("arcade.png");
    BRO::Player player("sprite_full.png");

    while(window.isOpen()){
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }

        player.animate();
        cursor.update();

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            player.setTarget();
        }

        window.setView(arcade.view);

        window.clear(sf::Color::Black);

        //window.draw(bedroom.roomSprite);
        //window.draw(shop.roomSprite);
        window.draw(arcade.roomSprite);
        window.draw(player.playerSprite);
        window.draw(cursor.cursorSprite);

        window.display();

    }
    return 0;
}
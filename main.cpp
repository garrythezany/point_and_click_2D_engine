#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

using namespace std;

sf::RenderWindow window;

// Multiplier for 320x200px base resolution
unsigned int resMultiplier = 6;
float resMultiplierF = resMultiplier;

// Classes
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
            cursorSprite.setOrigin(8, 8);
            cursorSprite.scale(resMultiplier, resMultiplier);
            cursorSprite.setPosition(400, 400);
        }
        void update(){
            cursorSprite.setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
        }
    };

    class Player{
    private:
        sf::Texture playerTexture;

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

        // Cycle through animation frames
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
                //playerTexture.update(window);
            }
        }

        void setTarget(){
            moveTarget = sf::Vector2f(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
        }

        void walk(){
            sf::Vector2f direction = sf::Vector2f(moveTarget.x, moveTarget.y) - playerSprite.getPosition();
            float magnitude = sqrt((direction.x * direction.x) + (direction.y * direction.y));
            sf::Vector2f unitVector((direction.x * 1.3f) / magnitude, direction.y / (magnitude * 1.8f));

            // overall player-speed
            playerSprite.move(unitVector * 0.8f * resMultiplierF);

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

    class Item{
    private:
        sf::Texture texture;

    public:
        sf::Sprite sprite;

        Item(const string filePath, float positionX, float positionY){
            texture.loadFromFile(filePath);
            sprite.setTexture(texture);
            sprite.scale(resMultiplier, resMultiplier);
            sprite.setPosition(positionX, positionY);
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

    BRO::Item test("cursor.png", 500, 500);



    sf::ConvexShape poly1;
    poly1.setPointCount(4);
    poly1.setPoint(0, sf::Vector2f(6 * resMultiplier, 126 * resMultiplier));
    poly1.setPoint(1, sf::Vector2f(58 * resMultiplier, 126 * resMultiplier));
    poly1.setPoint(2, sf::Vector2f(77 * resMultiplier, 115 * resMultiplier));
    poly1.setPoint(3, sf::Vector2f(88 * resMultiplier, 98 * resMultiplier));
    poly1.setFillColor(sf::Color(250, 0, 0, 180));
    sf::ConvexShape poly2;
    poly2.setPointCount(5);
    poly2.setPoint(0, sf::Vector2f(77 * resMultiplier, 115 * resMultiplier));
    poly2.setPoint(1, sf::Vector2f(164 * resMultiplier, 115 * resMultiplier));
    poly2.setPoint(2, sf::Vector2f(167 * resMultiplier, 106 * resMultiplier));
    poly2.setPoint(3, sf::Vector2f(166 * resMultiplier, 98 * resMultiplier));
    poly2.setPoint(4, sf::Vector2f(88 * resMultiplier, 98 * resMultiplier));
    poly2.setFillColor(sf::Color(0, 250, 0, 180));
    sf::ConvexShape poly3;
    poly3.setPointCount(6);
    poly3.setPoint(0, sf::Vector2f(167 * resMultiplier, 106 * resMultiplier));
    poly3.setPoint(1, sf::Vector2f(164 * resMultiplier, 115 * resMultiplier));
    poly3.setPoint(2, sf::Vector2f(164 * resMultiplier, 125 * resMultiplier));
    poly3.setPoint(3, sf::Vector2f(626 * resMultiplier, 125 * resMultiplier));
    poly3.setPoint(4, sf::Vector2f(569 * resMultiplier, 106 * resMultiplier));
    poly3.setPoint(5, sf::Vector2f(511 * resMultiplier, 106 * resMultiplier));
    poly3.setFillColor(sf::Color(0, 0, 250, 180));
    sf::ConvexShape poly4;
    poly4.setPointCount(4);
    poly4.setPoint(0, sf::Vector2f(511 * resMultiplier, 106 * resMultiplier));
    poly4.setPoint(1, sf::Vector2f(569 * resMultiplier, 106 * resMultiplier));
    poly4.setPoint(2, sf::Vector2f(550 * resMultiplier, 98 * resMultiplier));
    poly4.setPoint(3, sf::Vector2f(525 * resMultiplier, 98 * resMultiplier));
    poly4.setFillColor(sf::Color(0, 250, 0, 180));

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
        window.draw(poly1);
        window.draw(poly2);
        window.draw(poly3);
        window.draw(poly4);
        window.draw(test.sprite);
        window.draw(currentPlayer.playerSprite);
        window.draw(cursor.cursorSprite);

        window.display();
    }
    return 0;
}
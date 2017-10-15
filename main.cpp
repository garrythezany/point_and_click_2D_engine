#include <iostream>
#include <cstdarg>
#include <cmath>
#include <SFML/Graphics.hpp>

using namespace std;

sf::RenderWindow window;

// Multiplier for 320x200px base resolution
unsigned int resMultiplier = 6;
float resMultiplierF = resMultiplier;

// Classes
namespace BRO {

    //---------------------------
    // CURSOR
    //---------------------------
    class Cursor{
    private:
        sf::Texture texture;

    public:
        sf::Sprite sprite;

        // Constructor
        Cursor(){
            texture.loadFromFile("cursor.png");
            sprite.setTexture(texture);
            sprite.setOrigin(8, 8);
            sprite.setPosition(400, 400);
            sprite.scale(resMultiplier, resMultiplier);
        }
        void update(){
            sprite.setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
        }
    };

    //---------------------------
    // PLAYERS
    //---------------------------
    class Player{
    private:
        sf::Texture texture;

    public:
        // init Objects
        sf::IntRect mask;
        sf::Sprite sprite;
        sf::Clock clock;
        sf::Vector2f moveTarget;

        // Constructor
        explicit Player(const string &filePath){
            mask.left = 0;
            mask.top = 0;
            mask.width = 64;
            mask.height = 80;
            texture.loadFromFile(filePath);
            sprite.setTexture(texture);
            sprite.setTextureRect(mask);
            sprite.setOrigin(32, 77);
            sprite.setPosition(200 * resMultiplier, 115 * resMultiplier);

            // scale sprite based on y-axis,
            // where y = 100 * resMultiplier results in a scale of 1 * resMultiplier
            sprite.setScale(0.01f * (sprite.getPosition().y / resMultiplier) * resMultiplier,
                                  0.01f * (sprite.getPosition().y / resMultiplier) * resMultiplier);

            // The target, that the player moves towards
            moveTarget = sf::Vector2f(sprite.getPosition());
        }

        // Cycle through animation frames
        void iterateSprite(int top, int startLeft, int maxLeft, int incrementLeft, float speed){
            mask.top = top;
            if (clock.getElapsedTime().asSeconds() > speed){
                if (mask.left >= maxLeft) {
                    mask.left = startLeft;
                }
                else {
                    mask.left += incrementLeft;
                }
                sprite.setTextureRect(mask);
                //sprite.scale(resMultiplier / ((sprite.getPosition().y / resMultiplier) / 115),
                //                   resMultiplier / ((sprite.getPosition().y / resMultiplier) / 115));
                clock.restart();
                //texture.update(window);
            }
        }

        void setTarget(){
            moveTarget = sf::Vector2f(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
        }

        void walk(){
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

        void idle(){
            iterateSprite(0, 0, 448, 64, .2f);
        }

        void animate(){
            if (round(moveTarget.x) != round(sprite.getPosition().x) && round(moveTarget.y) != round(sprite.getPosition().y)){
                walk();
            } else {
                idle();
            }
        }

        int getPositionX(){
            float posF = sprite.getPosition().x;
            int posI = floor((posF * 100.0) + 0.5) / 100;
            return posI;
        }
    };

    //----------------------------
    // ROOMS
    //----------------------------
    class Room{
    private:
        sf::Texture texture;
        bool isScrollable;

    public:
        sf::View view;
        sf::FloatRect mask;
        sf::Sprite sprite;

        // max number of shapes hardcoded to 20
        sf::ConvexShape shapes[20];
        bool drawShapes;
        
        // constructor
        explicit Room(const string &filePath){
            mask.left = 0;
            mask.top = 0;
            mask.width = 320 * resMultiplier;
            mask.height = 200 * resMultiplier;
            view.reset(mask);
            texture.loadFromFile(filePath);
            sprite.setTexture(texture);
            sprite.scale(resMultiplier, resMultiplier);
            //cout << "size is " << texture.getSize().x << endl;
            if (texture.getSize().x != mask.width || texture.getSize().y != mask.height){
                isScrollable = true;
            } else {
                isScrollable = false;
            }
            // draw pathfinding shapes for debugging
            drawShapes = true;
        }

        void setShape(int shapeIndex, sf::ConvexShape &shape){
            shapes[shapeIndex] = shape;
        }

        void scrollHorizontal(float playerPositionX){
            if (isScrollable){
                if (playerPositionX > mask.width + mask.left - 100 * resMultiplier && texture.getSize().x * resMultiplier > mask.width + mask.left){
                    mask.left += 1 * resMultiplier;
                } else if (playerPositionX < mask.left + 100 * resMultiplier && mask.left > 0){
                    mask.left -= 1 * resMultiplier;
                }
            }
        }

        void drawRoom(){
            window.setView(view);
            window.draw(sprite);

            if (drawShapes){
                for (int i=0; i < 20; i++){
                    window.draw(shapes[i]);
                }
            }
        }
    };

    //-----------------------------
    // ITEMS
    //-----------------------------
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

    // test-shapes for arcade-room
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

    // Frame Clock
    sf::Clock clock;
    sf::Clock moveClock;

    BRO::Cursor cursor;
    //BRO::Room bedroom("bedroom.png");
    //BRO::Room shop("shop.png");
    BRO::Room arcade("arcade.png");
    arcade.setShape(0, poly1);
    arcade.setShape(1, poly2);
    arcade.setShape(2, poly3);
    arcade.setShape(3, poly4);
    BRO::Player player("sprite_full.png");

    BRO::Room currentRoom = arcade;
    BRO::Player currentPlayer = player;

    BRO::Item test("cursor.png", 500, 500);

    while(window.isOpen()){
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }

        currentPlayer.animate();
        cursor.update();

        bool clickedInWindow (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
            sf::Mouse::getPosition(window).x <= window.getSize().x &&
            sf::Mouse::getPosition(window).y <= window.getSize().y &&
            sf::Mouse::getPosition(window).x >= 0 &&
            sf::Mouse::getPosition(window).y >= 0);

        if(clickedInWindow){
            currentPlayer.setTarget();
        }


        currentRoom.scrollHorizontal(currentPlayer.sprite.getPosition().x);
        currentRoom.view.reset(currentRoom.mask);

        window.clear(sf::Color::Black);

        //window.draw(bedroom.sprite);
        //window.draw(shop.sprite);
        //window.draw(currentRoom.sprite);
        currentRoom.drawRoom();

        window.draw(currentPlayer.sprite);
        window.draw(cursor.sprite);

        window.display();
    }
    return 0;
}
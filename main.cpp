#include <iostream>
#include <SFML/Graphics.hpp>
#include "Cursor.cpp"
#include "Player.cpp"
#include "Room.cpp"

using namespace std;

//sf::RenderWindow window;

// Multiplier for 320x200px base resolution
unsigned int resMultiplier = 5;
float resMultiplierF = resMultiplier;


void renderPlayer(sf::RenderWindow &window, Player &player, Room &room) {
    // ---------------------------------
    // player config
    // ---------------------------------
    bool clickedInsideWindow = sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
                               sf::Mouse::getPosition(window).x <= window.getSize().x &&
                               sf::Mouse::getPosition(window).y <= window.getSize().y &&
                               sf::Mouse::getPosition(window).x >= 0 &&
                               sf::Mouse::getPosition(window).y >= 0;
    if(clickedInsideWindow) {
        player.setTarget(window);
    }
    player.animate();
    room.scrollHorizontal(player.playerSprite.getPosition().x);
    room.view.reset(room.viewMask);
}

// Classes
int main() {
    sf::RenderWindow window(sf::VideoMode(320 * resMultiplier, 200 * resMultiplier, 32), "Bronko Engine", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(90);
    window.setMouseCursorVisible(false);

    // ----------------------------------
    // Initialize Screen Variables
    // ----------------------------------
    Cursor cursor;
    Room arcade("arcade.png");
    Player player("sprite_full.png");

    Room currentRoom = arcade;
    Player currentPlayer = player;


    // ----------------------------------
    // Walk Area (test-room)
    // ----------------------------------
    sf::ConvexShape poly1;
    poly1.setPointCount(4);
    poly1.setPoint(0, sf::Vector2f(6 * 2, 126 * 2));
    poly1.setPoint(1, sf::Vector2f(58 * 2, 126 * 2));
    poly1.setPoint(2, sf::Vector2f(77 * 2, 115 * 2));
    poly1.setPoint(3, sf::Vector2f(88 * 2, 98 * 2));
    poly1.setFillColor(sf::Color(250, 0, 0, 180));
    sf::ConvexShape poly2;
    poly2.setPointCount(5);
    poly2.setPoint(0, sf::Vector2f(77 * 2, 115 * 2));
    poly2.setPoint(1, sf::Vector2f(164 * 2, 115 * 2));
    poly2.setPoint(2, sf::Vector2f(167 * 2, 106 * 2));
    poly2.setPoint(3, sf::Vector2f(166 * 2, 98 * 2));
    poly2.setPoint(4, sf::Vector2f(88 * 2, 98 * 2));
    poly2.setFillColor(sf::Color(0, 250, 0, 180));
    sf::ConvexShape poly3;
    poly3.setPointCount(6);
    poly3.setPoint(0, sf::Vector2f(167 * 2, 106 * 2));
    poly3.setPoint(1, sf::Vector2f(164 * 2, 115 * 2));
    poly3.setPoint(2, sf::Vector2f(164 * 2, 125 * 2));
    poly3.setPoint(3, sf::Vector2f(626 * 2, 125 * 2));
    poly3.setPoint(4, sf::Vector2f(569 * 2, 106 * 2));
    poly3.setPoint(5, sf::Vector2f(511 * 2, 106 * 2));
    poly3.setFillColor(sf::Color(0, 0, 250, 180));
    sf::ConvexShape poly4;
    poly4.setPointCount(4);
    poly4.setPoint(0, sf::Vector2f(511 * 2, 106 * 2));
    poly4.setPoint(1, sf::Vector2f(569 * 2, 106 * 2));
    poly4.setPoint(2, sf::Vector2f(550 * 2, 98 * 2));
    poly4.setPoint(3, sf::Vector2f(525 * 2, 98 * 2));
    poly4.setFillColor(sf::Color(0, 250, 0, 180));

    // lines from player to mouse
    sf::VertexArray line(sf::Lines, 2);



    // ---------------------------------
    // LOOP / TICK
    // ---------------------------------
    while(window.isOpen()){

        // ---------------------------------
        // Handle Events
        // ---------------------------------
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){

        }

        line[0].position = currentPlayer.playerSprite.getPosition();
        line[1].position = window.mapPixelToCoords(sf::Mouse::getPosition(window));


        // ---------------------------------
        // draw
        // ---------------------------------
        window.setView(currentRoom.view);
        window.clear(sf::Color::Black);
        window.draw(currentRoom.roomSprite);
        window.draw(poly1);
        window.draw(poly2);
        window.draw(poly3);
        window.draw(poly4);
        window.draw(currentPlayer.playerSprite);

        renderPlayer(window, currentPlayer, currentRoom);

        cursor.update(window);

        window.draw(cursor.sprite);
        window.draw(line);

        window.display();
    }
    return 0;
}

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Cursor.cpp"
#include "Player.cpp"
#include "Room.cpp"

using namespace std;
using namespace sf;

//sf::RenderWindow window;

// Multiplier for 320x200px base resolution
unsigned int resMultiplier = 7;
float resMultiplierF = resMultiplier;


void renderPlayer(RenderWindow &window, Player &player, Room &room) {
    // ---------------------------------
    // player config
    // ---------------------------------
    bool clickedInsideWindow = Mouse::isButtonPressed(Mouse::Left) &&
                               Mouse::getPosition(window).x <= window.getSize().x &&
                               Mouse::getPosition(window).y <= window.getSize().y &&
                               Mouse::getPosition(window).x >= 0 &&
                               Mouse::getPosition(window).y >= 0;
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


        // ---------------------------------
        // draw
        // ---------------------------------
        window.setView(currentRoom.view);
        window.clear(sf::Color::Black);
        window.draw(currentRoom.roomSprite);
        window.draw(currentPlayer.playerSprite);

        renderPlayer(window, currentPlayer, currentRoom);

        cursor.update(window);
        window.draw(cursor.sprite);

        window.display();
    }
    return 0;
}

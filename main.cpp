#include <iostream>
#include <SFML/Graphics.hpp>
#include "Cursor.cpp"
#include "Player.cpp"
#include "Room.cpp"

using namespace std;

//sf::RenderWindow window;

// Multiplier for 320x200px base resolution
unsigned int resMultiplier = 7;
float resMultiplierF = resMultiplier;

// Classes
int main() {
    sf::Event event;

    sf::RenderWindow window(sf::VideoMode(320 * resMultiplier, 200 * resMultiplier, 32), "Bronko Engine", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(90);
    window.setMouseCursorVisible(false);

    Cursor cursor;
    Room arcade("arcade.png");
    Player player("sprite_full.png");

    Room currentRoom = arcade;
    Player currentPlayer = player;

    while(window.isOpen()){
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }

        currentPlayer.animate();
        cursor.update(window);

        bool clickedInsideWindow = sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
                                   sf::Mouse::getPosition(window).x <= window.getSize().x &&
                                   sf::Mouse::getPosition(window).y <= window.getSize().y &&
                                   sf::Mouse::getPosition(window).x >= 0 &&
                                   sf::Mouse::getPosition(window).y >= 0;
        if(clickedInsideWindow)
        {
            currentPlayer.setTarget(window);
        }

        window.setView(currentRoom.view);
        currentRoom.scrollHorizontal(currentPlayer.playerSprite.getPosition().x);
        currentRoom.view.reset(currentRoom.viewMask);

        window.clear(sf::Color::Black);
        window.draw(currentRoom.roomSprite);
        window.draw(currentPlayer.playerSprite);
        window.draw(cursor.sprite);

        window.display();
    }
    return 0;
}

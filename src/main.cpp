#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "Game.h"

using namespace std;

BRO::Game game;

int main() {
    sf::Event event;
    game.window.create(sf::VideoMode(320 * game.resMultiplier, 200 * game.resMultiplier, 32), "PNR Engine", sf::Style::Titlebar | sf::Style::Close);
    game.window.setFramerateLimit(90);
    game.window.setMouseCursorVisible(false);

    //BRO::World world;
    //world.initStudioRoom(game.resMultiplier);
    BRO::Room studioRoom("studio.png", game.resMultiplier);

    // Frame Clock
    sf::Clock clock;
    sf::Clock moveClock;

    BRO::Cursor cursor;
    cursor.setScale(game.resMultiplier);
    //BRO::Room bedroom("bedroom.png");
    //BRO::Room shop("shop.png");



    BRO::Player player("sprite_full.png", game.resMultiplier);
    player.sprite.setPosition(100 * game.resMultiplier, 100 * game.resMultiplier);
    player.sprite.setScale(game.resMultiplier, game.resMultiplier);
    player.setTarget(sf::Vector2f(80 * game.resMultiplier, 140 * game.resMultiplier));

    BRO::Room currentRoom = studioRoom;
    BRO::Player currentPlayer = player;

    BRO::Item test("cursor.png", 500, 500, game.resMultiplier);

    while(game.window.isOpen()){
        while(game.window.pollEvent(event)) {
            if(event.type == sf::Event::Closed){
                game.window.close();
            }
        }

        currentPlayer.animate(game.resMultiplier, game.resMultiplierF);
        cursor.update(game.window.mapPixelToCoords(sf::Mouse::getPosition(game.window)));

        bool clickedInWindow (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
            sf::Mouse::getPosition(game.window).x <= game.window.getSize().x &&
            sf::Mouse::getPosition(game.window).y <= game.window.getSize().y &&
            sf::Mouse::getPosition(game.window).x >= 0 &&
            sf::Mouse::getPosition(game.window).y >= 0);

        if(clickedInWindow){
            currentPlayer.setTarget(game.window.mapPixelToCoords(sf::Mouse::getPosition(game.window)));
        }

        currentRoom.scrollHorizontal(currentPlayer.sprite.getPosition().x, game.resMultiplier);
        currentRoom.view.reset(currentRoom.mask);

        game.window.clear(sf::Color::Black);

        //window.draw(bedroom.sprite);
        //window.draw(shop.sprite);
        //window.draw(currentRoom.sprite);
        currentRoom.drawRoom(game.window);

        game.window.draw(currentPlayer.sprite);
        game.window.draw(cursor.sprite);

        game.window.display();
    }
    return 0;
}
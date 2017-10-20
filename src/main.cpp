#include <iostream>
#include "Game.h"

using namespace std;

int main() {
    BRO::Game game;

    static sf::Event event;

    // Set default game resolution
    // 1 = 320x200
    // 2 = 640x400
    // 3 = 960x600
    // 4 = 1280x800
    // 5 = 1600x1000
    // 6 = 1920x1200
    // 7 = 2240x1400
    // 8 = 2560x1600
    // 9 = 2880x1800
    game.setResMultiplier(6);

    game.window.create(sf::VideoMode(320 * game.resMultiplier, 200 * game.resMultiplier, 32), "PNC Engine", sf::Style::Titlebar | sf::Style::Close);
    game.window.setFramerateLimit(60);
    game.window.setMouseCursorVisible(false);
    //BRO::World world;
    //world.initStudioRoom(game.resMultiplier);
    BRO::Room studioRoom("studio.png", game.resMultiplier);

    BRO::Cursor cursor;
    cursor.setScale(game.resMultiplier);

    BRO::Player player("sprite_full.png", game.resMultiplier);
    player.sprite.setPosition(100 * game.resMultiplier, 100 * game.resMultiplier);
    player.sprite.setScale(game.resMultiplier, game.resMultiplier);
    player.setTarget(sf::Vector2f(80 * game.resMultiplier, 140 * game.resMultiplier));

    BRO::Room currentRoom = studioRoom;
    BRO::Player currentPlayer = player;

    BRO::Music track1("track1.ogg");
    track1.audio.setVolume(40);

    while(game.window.isOpen()){
        while(game.window.pollEvent(event)) {
            if(event.type == sf::Event::Closed){
                game.window.close();
            }
        }

        track1.loop();

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

        currentRoom.drawRoom(game.window);

        game.window.draw(currentPlayer.sprite);
        game.window.draw(cursor.sprite);

        game.window.display();
    }
    return 0;
}

#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "Game.h"

using namespace std;

BRO::Game game;

int main() {
    sf::Event event;
    game.window.create(sf::VideoMode(320 * game.resMultiplier, 200 * game.resMultiplier, 32),"Bronko Engine", sf::Style::Titlebar | sf::Style::Close);
    game.window.setFramerateLimit(90);
    game.window.setMouseCursorVisible(false);

    // test-shapes for arcade-room
    sf::ConvexShape poly1;
    poly1.setPointCount(4);
    poly1.setPoint(0, sf::Vector2f(6 * game.resMultiplier, 126 * game.resMultiplier));
    poly1.setPoint(1, sf::Vector2f(58 * game.resMultiplier, 126 * game.resMultiplier));
    poly1.setPoint(2, sf::Vector2f(77 * game.resMultiplier, 115 * game.resMultiplier));
    poly1.setPoint(3, sf::Vector2f(88 * game.resMultiplier, 98 * game.resMultiplier));
    poly1.setFillColor(sf::Color(250, 0, 0, 180));
    sf::ConvexShape poly2;
    poly2.setPointCount(5);
    poly2.setPoint(0, sf::Vector2f(77 * game.resMultiplier, 115 * game.resMultiplier));
    poly2.setPoint(1, sf::Vector2f(164 * game.resMultiplier, 115 * game.resMultiplier));
    poly2.setPoint(2, sf::Vector2f(167 * game.resMultiplier, 106 * game.resMultiplier));
    poly2.setPoint(3, sf::Vector2f(166 * game.resMultiplier, 98 * game.resMultiplier));
    poly2.setPoint(4, sf::Vector2f(88 * game.resMultiplier, 98 * game.resMultiplier));
    poly2.setFillColor(sf::Color(0, 250, 0, 180));
    sf::ConvexShape poly3;
    poly3.setPointCount(6);
    poly3.setPoint(0, sf::Vector2f(167 * game.resMultiplier, 106 * game.resMultiplier));
    poly3.setPoint(1, sf::Vector2f(164 * game.resMultiplier, 115 * game.resMultiplier));
    poly3.setPoint(2, sf::Vector2f(164 * game.resMultiplier, 125 * game.resMultiplier));
    poly3.setPoint(3, sf::Vector2f(626 * game.resMultiplier, 125 * game.resMultiplier));
    poly3.setPoint(4, sf::Vector2f(569 * game.resMultiplier, 106 * game.resMultiplier));
    poly3.setPoint(5, sf::Vector2f(511 * game.resMultiplier, 106 * game.resMultiplier));
    poly3.setFillColor(sf::Color(0, 0, 250, 180));
    sf::ConvexShape poly4;
    poly4.setPointCount(4);
    poly4.setPoint(0, sf::Vector2f(511 * game.resMultiplier, 106 * game.resMultiplier));
    poly4.setPoint(1, sf::Vector2f(569 * game.resMultiplier, 106 * game.resMultiplier));
    poly4.setPoint(2, sf::Vector2f(550 * game.resMultiplier, 98 * game.resMultiplier));
    poly4.setPoint(3, sf::Vector2f(525 * game.resMultiplier, 98 * game.resMultiplier));
    poly4.setFillColor(sf::Color(0, 250, 0, 180));
    // test-nodes
    BRO::Node A;
    BRO::Node B;
    BRO::Node C;
    BRO::Node D;
    // assigning adjacent nodes
    A.addAdjacent(B);
    B.addAdjacent(A);
    B.addAdjacent(C);
    C.addAdjacent(B);
    C.addAdjacent(D);
    D.addAdjacent(C);
    // create BRO::Polygons containing a convexShape + a node
    BRO::Polygon aPoly;
    BRO::Polygon bPoly;
    BRO::Polygon cPoly;
    BRO::Polygon dPoly;
    aPoly.assign(poly1, A);
    aPoly.assign(poly2, B);
    aPoly.assign(poly3, C);
    aPoly.assign(poly4, D);
    // now we have Polygons with
    //      a Node + corresponding adjacent nodes
    //      a Shape + corresponding vertices
    BRO::NavMesh arcadeNavMesh;
    arcadeNavMesh.addPoly(aPoly);
    arcadeNavMesh.addPoly(bPoly);
    arcadeNavMesh.addPoly(cPoly);
    arcadeNavMesh.addPoly(dPoly);

    // testing NavMesh data - should print "6"
    cout << arcadeNavMesh.polyList[2].shape.getPointCount() << endl;

    // Frame Clock
    sf::Clock clock;
    sf::Clock moveClock;

    BRO::Cursor cursor;
    cursor.setScale(game.resMultiplier);
    //BRO::Room bedroom("bedroom.png");
    //BRO::Room shop("shop.png");
    BRO::Room arcade("arcade.png", game.resMultiplier);
    arcade.setShape(0, poly1);
    arcade.setShape(1, poly2);
    arcade.setShape(2, poly3);
    arcade.setShape(3, poly4);

    arcade.setNavMesh(arcadeNavMesh);

    BRO::Player player("sprite_full.png", game.resMultiplier);
    player.sprite.setPosition(100 * game.resMultiplier, 140 * game.resMultiplier);
    player.sprite.setScale(game.resMultiplier, game.resMultiplier);
    player.setTarget(sf::Vector2f(80 * game.resMultiplier, 140 * game.resMultiplier));

    BRO::Room currentRoom = arcade;
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

        cout << currentPlayer.sprite.getPosition().x << " x " << currentPlayer.sprite.getPosition().y << endl;


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
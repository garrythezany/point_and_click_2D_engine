//
// Created by Roman Hock on 19.10.17.
//

#include "World.h"

//--------------------
// ARCADE ROOM - TEST
//--------------------
void BRO::World::initArcadeRoom(int resMultiplier){
    //------------------
    // Room Setup
    //------------------
    BRO::Room arcade("arcade.png", resMultiplier);
    //----------------------------
    // NavMesh Setup
    //----------------------------
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
    // nodes
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

    arcade.setShape(0, poly1);
    arcade.setShape(1, poly2);
    arcade.setShape(2, poly3);
    arcade.setShape(3, poly4);

    arcade.setNavMesh(arcadeNavMesh);
}

//--------------------
// STUDIO ROOM - TEST
//--------------------
void BRO::World::initStudioRoom(int resMultiplier) {
    //------------------
    // Room Setup
    //------------------
    BRO::Room arcade("studio.png", resMultiplier);
    //----------------------------
    // NavMesh Setup
    //----------------------------
}

//--------------------
// WORLD
//--------------------
void BRO::World::initWorld(int resMultiplier){
    initStudioRoom(resMultiplier);
    initArcadeRoom(resMultiplier);
}
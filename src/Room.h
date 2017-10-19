//
// Created by Roman Hock on 19.10.17.
//

#ifndef SFML_ROOM_H
#define SFML_ROOM_H

#include <SFML/Graphics.hpp>
#include "NavMesh.h"
#include "Game.h"

namespace BRO{
    class Room{
    private:
        sf::Texture texture;
        bool isScrollable;

    public:
        sf::View view;
        sf::FloatRect mask;
        sf::Sprite sprite;
        BRO::NavMesh navMesh;

        // max number of shapes hardcoded to 20
        sf::ConvexShape shapes[20];
        bool drawShapes;

        // constructor
        Room(const std::string &filePath, int resMultiplier);

        void setShape(int shapeIndex, sf::ConvexShape &shape);

        void scrollHorizontal(float playerPositionX, float resMultiplier);

        void setNavMesh(const BRO::NavMesh &_navMesh);

        void drawRoom(sf::RenderWindow &window);
    };
}


#endif //SFML_ROOM_H

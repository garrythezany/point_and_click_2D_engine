//
// Created by Roman Hock on 19.10.17.
//

#ifndef SFML_PLAYER_H
#define SFML_PLAYER_H

#include <SFML/Graphics.hpp>
#include <cmath>

namespace BRO{
    class Player {
    private:
        sf::Texture texture;

    public:
        // init Objects
        sf::IntRect mask;
        sf::Sprite sprite;
        sf::Clock clock;
        sf::Vector2f moveTarget;

        // Constructor
        Player(const std::string &filePath, int resMultiplier);

        // Cycle through animation frames
        void iterateSprite(int top, int startLeft, int maxLeft, int incrementLeft, float speed);

        void setTarget(sf::Vector2f coordinates);

        void walk(int resMultiplier, float resMultiplierF);

        void idle();

        void animate(int resMultiplier, float resMultiplierF);

        int getPositionX();
    };

}

#endif //SFML_PLAYER_H

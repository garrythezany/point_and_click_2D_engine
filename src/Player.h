#ifndef PNR_Engine_PLAYER_H
#define PNR_Engine_PLAYER_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include "Game.h"

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
        sf::Clock moveClock;

        float positiveDirectionX;
        float positiveDirectionY;

        // Constructor
        Player(const std::string &filePath, unsigned int &resMultiplier);

        // Cycle through animation frames
        void iterateSprite(int top, int startLeft, int maxLeft, int incrementLeft, float speed);

        void setTarget(sf::Vector2f coordinates);

        void walk(unsigned int &resMultiplier, float &resMultiplierF);

        void idle();

        void animate(unsigned int &resMultiplier, float &resMultiplierF);

        int getPositionX();
    };
}

#endif //PNR_Engine_PLAYER_H

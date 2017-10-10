//
// Created by Bastian Wegge on 10.10.17.
//
#include <SFML/Graphics.hpp>

using namespace std;

class Room{
private:
    sf::Texture roomTexture;
    bool isScrollable;

public:
    sf::View view;
    sf::FloatRect viewMask;
    sf::Sprite roomSprite;
    float moveTargetX;
    // constructor
    explicit Room(const string &filePath){
        viewMask.left = 0;
        viewMask.top = 0;
        viewMask.width = 320 * 2.0f;
        viewMask.height = 200 * 2.0f;
        view.reset(viewMask);
        roomTexture.loadFromFile(filePath);
        roomSprite.setTexture(roomTexture);
        roomSprite.scale(2.0f, 2.0f);
        //cout << "size is " << roomTexture.getSize().x << endl;
        if (roomTexture.getSize().x != viewMask.width || roomTexture.getSize().y != viewMask.height){
            isScrollable = true;
        } else {
            isScrollable = false;
        }
    }

    void scrollHorizontal(float playerPositionX){
        if (isScrollable){
            if (playerPositionX > viewMask.width + viewMask.left - 100 * 2.0f && roomTexture.getSize().x * 2.0f > viewMask.width + viewMask.left){
                viewMask.left += 1 * 2.0f;
            } else if (playerPositionX < viewMask.left + 100 * 2.0f && viewMask.left > 0){
                viewMask.left -= 1 * 2.0f;
            }
        }
    }
};
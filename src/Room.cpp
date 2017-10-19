#include "Room.h"

BRO::Room::Room(const std::string &filePath, unsigned int &resMultiplier){
    mask.left = 0;
    mask.top = 0;
    mask.width = 320 * resMultiplier;
    mask.height = 200 * resMultiplier;
    view.reset(mask);
    texture.loadFromFile(filePath);
    sprite.setTexture(texture);
    sprite.scale(resMultiplier, resMultiplier);
    //cout << "size is " << texture.getSize().x << endl;
    if (texture.getSize().x != mask.width || texture.getSize().y != mask.height){
        isScrollable = true;
    } else {
        isScrollable = false;
    }
    // draw pathfinding shapes for debugging
    drawShapes = true;
}

void BRO::Room::setShape(int shapeIndex, sf::ConvexShape &shape){
    shapes[shapeIndex] = shape;
}

void BRO::Room::scrollHorizontal(float playerPositionX, unsigned int &resMultiplier){
    if (isScrollable){
        if (playerPositionX > mask.width + mask.left - 100 * resMultiplier && texture.getSize().x * resMultiplier > mask.width + mask.left){
            mask.left += 1 * resMultiplier;
        } else if (playerPositionX < mask.left + 100 * resMultiplier && mask.left > 0){
            mask.left -= 1 * resMultiplier;
        }
    }
}

void BRO::Room::setNavMesh(const BRO::NavMesh &_navMesh){
    navMesh = _navMesh;
}

void BRO::Room::drawRoom(sf::RenderWindow &window){
    window.setView(view);
    window.draw(sprite);

    if (drawShapes){
        for (int i=0; i < 20; i++){
            window.draw(shapes[i]);
        }
    }
}
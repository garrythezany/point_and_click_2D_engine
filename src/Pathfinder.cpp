#include "Pathfinder.h"

void BRO::Node::addAdjacent(const Node &node) {
    adjacencyList.push_back(node);
}

void BRO::Polygon::assign(sf::ConvexShape &_shape, BRO::Node &_node) {
    shape = _shape;
    node = _node;
}

void BRO::NavMesh::addPoly(BRO::Polygon &poly) {
    polyList.push_back(poly);
}

void BRO::NavMesh::addShape(sf::ConvexShape &shape){
    shapeList.push_back(shape);
};

bool BRO::Pathfinder::CCW(const std::vector<sf::Vector2f>& points){
    if (points.size() != 3)
        return false;

    return (points[2].y - points[0].y) * (points[1].x - points[0].x) > (points[1].y - points[0].y) * (points[2].x - points[0].x);
}

bool BRO::Pathfinder::doLinesIntersect(const std::vector<std::vector<sf::Vector2f>>& lines)
{
    if (lines.size() != 2)
        return false;
    if ((lines[0].size() != 2) || (lines[1].size() != 2))
        return false;

    return	(CCW({ lines[0][0], lines[1][0], lines[1][1] }) != CCW({ lines[0][1], lines[1][0], lines[1][1] })) &&
              (CCW({ lines[0][0], lines[0][1], lines[1][0] }) != CCW({ lines[0][0], lines[0][1], lines[1][1] }));
}

bool BRO::Pathfinder::isPointInsidePolygon(const sf::Vector2f& point, const std::vector<sf::Vector2f>& polygonVertices)
{
    return isPointInsidePolygon(point, polygonVertices, boundingBox(polygonVertices));
}

bool BRO::Pathfinder::isPointInsidePolygon(const sf::Vector2f& point, const std::vector<sf::Vector2f>& polygonVertices, const sf::FloatRect& boundingBox)
{
    if (!boundingBox.contains(point))
        return false;

    bool isInside{ false };
    sf::Vector2f pointOutsideBoundingBox{ boundingBox.left - 1, boundingBox.top - 1 };
    for (unsigned int v{ 0 }, w{ static_cast<unsigned int>(polygonVertices.size()) - 1 }; v < polygonVertices.size(); w = v++)
    {
        if (doLinesIntersect({ { polygonVertices[v], polygonVertices[w] }, { pointOutsideBoundingBox, point } }))
            isInside = !isInside;
    }
    return isInside;
}

sf::FloatRect BRO::Pathfinder::boundingBox(const std::vector<sf::Vector2f>& vertices)
{
    sf::FloatRect box;
    if (vertices.size() > 0)
    {
        box.left = vertices[0].x;
        box.top = vertices[0].y;
    }
    // store bottom right corner otherwise moving the top or left of the box would require also adjusting the width and height to compensate
    sf::Vector2f bottomRight{ vertices[0] };
    for (auto& vertex : vertices)
    {
        if (vertex.x < box.left)
            box.left = vertex.x;
        else if (vertex.x > bottomRight.x)
            bottomRight.x = vertex.x;
        if (vertex.y < box.top)
            box.top = vertex.y;
        else if (vertex.y > bottomRight.y)
            bottomRight.y = vertex.y;
    }
    box.width = bottomRight.x - box.left;
    box.height = bottomRight.y - box.top;

    return box;
}

void BRO::Pathfinder::validPolygon(BRO::NavMesh &navMesh, BRO::Player &player, BRO::Cursor &cursor) {

    for (int i = 0; i < navMesh.shapeList.size(); i++){
        int counter = 0;
        std::vector<sf::Vector2f> line;
        std::vector<sf::Vector2f> playerCursorLine;
        std::vector<std::vector<sf::Vector2f>> lines;
        if (navMesh.shapeList[i].getGlobalBounds().contains(cursor.sprite.getPosition())){
            //bool validPoly = false;
            for (int n = 1; n < navMesh.shapeList[i].getPointCount(); n++){
                line.push_back(navMesh.shapeList[i].getPoint(n));
                line.push_back(navMesh.shapeList[i].getPoint(n+1));
                playerCursorLine.push_back(player.sprite.getPosition());
                playerCursorLine.push_back(cursor.sprite.getPosition());
                lines.push_back(line);
                lines.push_back(playerCursorLine);
                if (BRO::Pathfinder::doLinesIntersect(lines)){
                    counter += 1;
                }
                line.clear();
                playerCursorLine.clear();
                lines.clear();
            }
            if (counter == 1){
                std::cout << "You clicked a valid Polygon" << std::endl;
            }
        }
    }

}
#include "TileMapBank.h"

TileMapBank::TileMapBank(){}

bool TileMapBank::init()
{
    _mapBank.push_back(TileMap(sf::Vector2f(4.0f, 4.0f)));
    int mapOne[20] =
    {
        0, 1, 1, 0,
        1, 0, 0, 1,
        1, 0, 0, 1,
        1, 0, 0, 1,
        0, 1, 1, 0
    };
    _mapBank.at(0).build(mapOne, 5, 4, "tileset.png");
}

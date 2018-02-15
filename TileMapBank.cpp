#include "TileMapBank.h"

TileMapBank::TileMapBank() {}

bool TileMapBank::init()
{
	TileMap* testMap = new TileMap(sf::Vector2f(10.0f, 10.0f));
    _mapBank.push_back(testMap);
    int mapOne[20] =
    {
        0, 1, 1, 0,
        1, 0, 0, 1,
        1, 0, 0, 1,
        1, 0, 0, 1,
        0, 1, 1, 0
    };
    _mapBank.at(0)->build(mapOne, 5, 4, "tileset.png");
	return true;
}

TileMap& TileMapBank::getMap() {
	return *(_mapBank.at(0));
}
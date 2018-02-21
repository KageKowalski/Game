#include "TileMapBank.h"

TileMapBank::TileMapBank() {}

bool TileMapBank::init()
{
	TileMap* testMap = new TileMap(sf::Vector2f(10.0f, 10.0f));
    _mapBank.push_back(testMap);
    int mapOne[100] =
    {
        0,0,0,2,1,1,1,1,1,1,
        0,0,0,2,1,1,1,1,1,1,
        0,0,0,2,1,1,1,1,1,1,
        0,0,0,2,1,1,1,1,1,1,
        0,0,0,0,2,2,1,1,1,1,
        0,0,0,0,0,2,1,1,1,1,
        0,0,0,0,0,2,1,1,1,1,
        0,0,0,0,0,0,2,1,1,1,
        0,0,0,0,0,0,0,2,2,2,
        0,0,0,0,0,0,0,0,0,0
    };
    _mapBank.at(0)->build(mapOne, 10, 10, "tilesettest.png");
	return true;
}

TileMap& TileMapBank::getMap() {
	return *(_mapBank.at(0));
}

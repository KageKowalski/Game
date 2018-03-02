//Josh Seelye
#include "TileMapBank.h"

TileMapBank::TileMapBank() {}

TileMapBank::~TileMapBank() {
	for (size_t i = 0; i < _mapBank.size(); i++)
		delete[] _mapBank.at(i);
}

bool TileMapBank::init()
{
	TileMap* testMap = new TileMap(sf::Vector2f(10.0f, 10.0f), "Game_Test.wav");
    _mapBank.push_back(testMap);
    int blank[1] = { -2 };
    int mapOne[100] =
    {
        13,13,13,13,13,13,13,13,13,13,
        13,1,2,2,2,2,2,2,3,13,
        13,8,0,0,0,0,0,0,4,13,
        13,8,0,0,0,0,0,0,4,13,
        13,8,0,0,0,0,0,0,4,13,
        13,8,0,0,0,0,0,0,4,13,
        13,8,0,0,0,0,0,0,4,13,
        13,8,0,0,0,0,0,0,4,13,
        13,7,6,6,6,6,6,6,5,13,
        13,13,13,13,13,13,13,13,13,13
    };
    _mapBank.at(0)->build(mapOne, blank, blank, blank, blank, 10, 10, "TestTileSet.png");
	return true;
}

TileMap& TileMapBank::getMap() {
	return *(_mapBank.at(0));
}

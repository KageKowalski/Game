#include "TileMap.h"

/********************************
    Tile Functions/Constructors
 ********************************/

TileMap::Tile::Tile()       : tileID(-1){}
TileMap::Tile::Tile(int ID) : tileID(ID){}

int TileMap::Tile::getID()       { return tileID; }
void TileMap::Tile::setID(int ID){ tileID = ID;   }


/********************************
  TileMap Functions/Constructors
 ********************************/

TileMap::TileMap() {}

bool TileMap::build(int** intMap, int width, int height, std::string tilesetFileName)
{
    if(!_tileset.loadFromFile(tilesetFileName)) return false;
    _width = width;
    _height = height;
    _map = new Tile*[_height];
    for(int i = 0; i<_height;i++) _map[i] = new Tile[_width];
    
    for(int i = 0; i < _height; i++)
    {
        for(int j = 0; j < _width; j++)
        {
            _map[i][j] = Tile(intMap[i][j]);
        }
    }
    return true;
}

TileMap::~TileMap()
{
    for(int i = 0; i < _height; i++)
    {
        delete[] _map[i];
    }
    delete[] _map;
}

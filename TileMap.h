#ifndef TileMap_hpp
#define TileMap_hpp

#include <stdio.h>
#include <vector>
#include <SFML/Graphics.hpp>

class TileMap
{
    class Tile
    {
    private:
        int tileID;
    public:
        Tile();
        Tile(int ID);
        
        int  getID();
        void setID(int ID);
    };
    
private:
    Tile** _map;
    sf::Texture _tileset;
    int _width;
    int _height;
    
public:
    TileMap();
    bool build(int** intMap, int width, int height, std::string tilesetFileName);
    ~TileMap();
    
};

#endif /* TileMap_h */

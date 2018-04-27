#ifndef TileSet_hpp
#define TileSet_hpp

#include "Tile.h"

class TileCollection
{
public:
    //populates the tile vector
    TileCollection();
    
    const Tile* getTileFromID(int ID) const;
    
    void update();
    
private:
    
    std::vector<Tile*> _loadedTiles;
    
};

#endif

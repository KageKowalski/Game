#ifndef TileMapBank_hpp
#define TileMapBank_hpp

#include <stdio.h>
#include "TileMap.h"

class TileMapBank
{
private:
    std::vector<TileMap*> _mapBank;
    
public:
    TileMapBank();
    
    bool init();
    
	TileMap& getMap();
    
};

#endif /* TileMapBank_hpp */

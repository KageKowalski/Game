#include "TileCollection.h"

TileCollection::TileCollection()
{
    for(int ID = 0; ID < 600; ID++)
    {
        Tile* next;
        switch (ID)
        {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
            case 12:
                next = new Tile(ID, 0x05, "waves.wav");
                break;
            case 13:
            case 14:
            case 15:
            case 16:
            case 17:
            case 18:
            case 19:
            case 20:
            case 21:
            case 22:
            case 23:
            case 24:
            case 25:
                next = new Tile(ID, 0x02, "grass_foot.wav");
                break;
            case 28:
                next = new Tile(ID,0x01);
                break;
            case 52:
            case 53:
            case 54:
                next = new Tile(ID, 0x10);
                break;
            case 92:
                next = new Tile(ID, 0x09);
                break;
            default:
                next = new Tile(ID);
                break;
                
        }
        _loadedTiles.push_back(next);
    }
}

const Tile* TileCollection::getTileFromID(int ID) const
{
    if(ID == -1) return new Tile();
    return _loadedTiles.at(ID);
    
}

void TileCollection::update()
{
    for(int i = 0; i < _loadedTiles.size(); i++)
    {
        _loadedTiles[i]->update();
    }
}

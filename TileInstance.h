#ifndef TileInstance_h
#define TileInstance_h

#include "Tile.h"

class TileInstance : public Collidable, public EventListener
{
public:
    //can't create a standard tile instance
    TileInstance();
    
    //main constructor/ destructor
    TileInstance(const Tile& tile, const sf::Vector2f& position);
    ~TileInstance();
    
    //returns position of tile instance
    const sf::Vector2f& getPosition() const;
    
    //returns center position of tile instance
    const sf::Vector2f& getCenterPosition() const;
    
    //return a pointer the the tile
    const Tile* getTile() const;
    
    //sets the position then sets the center position;
    void setPosition(const sf::Vector2f& position);
    
    //makes this instance point to a new tile
    void setTile(const Tile& tile);
    
    bool collision(const Collidable& obj) const override;
    
    sf::FloatRect getGlobalBounds() const override;
    
    void handleEvent(Event* const e) override;
private:
    //basic instance variables
    const Tile*  _tile;
    sf::Vector2f _position;
    sf::Vector2f _centerPosition;
};

#endif

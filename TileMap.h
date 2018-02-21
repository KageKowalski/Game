#ifndef TileMap_hpp
#define TileMap_hpp

#include <stdio.h>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Random.h"

class TileMap : public sf::Transformable, public sf::Drawable
{
    class Tile : public sf::Transformable
    {
    private:
        int tileID;
        int styles;
    
    public:
        Tile();
        Tile(int ID, const sf::Vector2f& position);
        
        int  getID();
        void setID(int ID);
        int  getStyleAmount();
    };
    
private:
    Tile** _map;
    sf::Texture _tileset;
    Random tileSelect;
    int _width;
    int _height;
	sf::VertexArray m_Verticies;
    
public:
    TileMap(const sf::Vector2f& scale);
    bool build(int* intMap, int width, int height, std::string tilesetFileName);
    virtual ~TileMap();

private:
	void vertexFill(int y, int x);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
};

#endif /* TileMap_h */

//Josh Seelye
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
        int steps;
    
    public:
        Tile();
        Tile(int ID, const sf::Vector2f& position);
        
        int  getID();
        void setID(int ID);
        int  getStepAmount();
    };
    
private:
    Tile** _ground;
    Tile** _layerOne;
    Tile** _layerTwo;
    sf::Texture _tileset;
    int _width;
    int _height;
	sf::VertexArray m_groundVerticies;
    
public:
    TileMap(const sf::Vector2f& scale);
    bool build(int* ground, int* layerOne, int* layerTwo, int width, int height, std::string tilesetFileName);
    virtual ~TileMap();

private:
	void vertexFill(int y, int x);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
};

#endif /* TileMap_h */

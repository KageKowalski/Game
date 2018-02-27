//Josh Seelye
#ifndef TileMap_hpp
#define TileMap_hpp

#include <stdio.h>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Random.h"
#include "AutoAnimation.h"
#include "TileSet.h"

class TileMap : public sf::Transformable, public sf::Drawable
{
    class Tile : public sf::Transformable
    {
    private:
        AutoAnimation animate;
        int tileID;
        int step;
    
    public:
        Tile();
        Tile(int ID, const sf::Vector2f& position);
        
        void updateAnimStep(sf::Time);
        
        int  getID();
        void setID(int ID);
        int getAnimStep();

    };
    
private:
    Tile** _ground;
    Tile** _layerOne;
    Tile** _layerTwo;
    TileSet _tileset;
    int _width;
    int _height;
	sf::VertexArray _groundVerticies;
    
public:
    TileMap(const sf::Vector2f& scale);
    bool build(int* ground, int* layerOne, int* layerTwo, int width, int height, std::string tilesetFileName);
    void updateMap(sf::Time);
    virtual ~TileMap();

private:
	void vertexFill(int y, int x);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
};

#endif /* TileMap_h */

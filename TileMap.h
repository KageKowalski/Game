//Josh Seelye
#ifndef TileMap_hpp
#define TileMap_hpp

#include <stdio.h>
#include <vector>
#include <SFML/Graphics.hpp>
#include "AutoAnimation.h"
#include "TileSet.h"

class TileMap : public sf::Transformable
{
    class Tile
    {
    private:
        AutoAnimation _animate;
        int _tileID;
        int _step;
        sf::Vector2f _position;
        
        AutoAnimation getTileAnimation(int ID);
    
    public:
        Tile();
        Tile(int ID, const sf::Vector2f& position);
        
        void updateAnimStep(sf::Time);
        
        int  getID();
        void setID(int ID);
        int getAnimStep();
        const sf::Vector2f& getPosition() const;

    };
    
private:
    Tile** _ground;
    Tile** _layerOne;
    Tile** _layerTwo;
    TileSet _tileset;
    int _width;
    int _height;
	sf::VertexArray _groundVerticies;
    sf::VertexArray _layerOneVerticies;
    sf::VertexArray _layerTwoVerticies;
    std::string _music;
    
public:
    TileMap(const sf::Vector2f& scale, std::string music);
    
    bool build(int* ground, int* layerOne, int* layerTwo, int width, int height, std::string tilesetFileName);
    void updateMap(sf::Time);
    
    const sf::VertexArray& getGroundVertices()   const;
    const sf::VertexArray& getLayerOneVertices() const;
    const sf::VertexArray& getLayerTwoVertices() const;
    const sf::Texture&     getTileSet()          const;
    const sf::Transform&   getTransform()        const;
    std::string getMusic();
    
    virtual ~TileMap();

private:
	void vertexFill(int y, int x);
    
};

#endif /* TileMap_h */

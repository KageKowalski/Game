#ifndef TileMap_hpp
#define TileMap_hpp

#include <stdio.h>
#include <vector>
#include <SFML/Graphics.hpp>

class TileMap : public sf::Transformable, public sf::Drawable
{
    class Tile : public sf::Transformable
    {
    private:
        int tileID;
    public:
        Tile();
        Tile(int ID, const sf::Vector2f& position);
        
        int  getID();
        void setID(int ID);
    };
    
private:
    Tile** _map;
    sf::Texture _tileset;
    int _width;
    int _height;
	sf::VertexArray m_Verticies;
    
public:
    TileMap(const sf::Vector2f& scale);
    bool build(int** intMap, int width, int height, std::string tilesetFileName);
    virtual ~TileMap();

private:
	void vertexFill(int i, int j);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
};

#endif /* TileMap_h */

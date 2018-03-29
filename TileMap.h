//Josh Seelye
#ifndef TileMap_h
#define TileMap_h

#include <map>
#include "Tile.h"
#include "EventBus.h"


class TileMap
{
public:
    struct LayeredTile
    {
        Tile*  ground;
        Tile*  layerTwo;
        Tile*  layerThree;
        Tile*  layerSix;
        Tile*  canopy;
    };
private:
    //layer 1 with the background being considered layer 0
    //layer 4 and 5 are sprite sheets
    //these layers are loaded from top to bottom meaning that canopy will be displayed above ground
    Tile**  _ground;
    Tile**  _layerTwo;
    Tile**  _layerThree;
    Tile**  _layerSix;
    Tile**  _canopy;
    TileSet _tileset;
    int**   _movementMap;
    
    std::map<int, LayeredTile*> _map;
    
    //width and height of the current tilemap
    int _width;
    int _height;
    
    //containes all of the vertex positions for the textures
	sf::VertexArray _groundVerticies;
    sf::VertexArray _layerTwoVerticies;
    sf::VertexArray _layerThreeVerticies;
    sf::VertexArray _layerSixVerticies;
    sf::VertexArray _canopyVerticies;
    
    //each map will have a identifier and an array that contains all maps they are connected to
    //this allows us to know what maps should be rendered at any given time
    int  _mapIdentifier;
    int* _mapLinks;
    
    //background music for each map
    //this cannot be changed after initialization
    std::string _music;
    
    //name of map/area
    std::string _name;
    
public:
    //basic constructor
    TileMap(std::string name);
    
    //builds the map and returns true on a successful build
    //send maps with a -1 value for invalid textures
    //if a map has a -2 value in the 0 position the map will be thrown out
    bool build(int* ground, int* layerTwo, int* layerThree, int* layerSix, int* canopy, int width, int height, std::string Music, std::string tilesetFileName);
    
    //updates all animated tiles in the map
    void updateMap();
    
    int ** getMovementMap() const;
    
    //returns the vertexarrays from the corresponding layer
    const sf::VertexArray& getGroundVertices()     const;
    const sf::VertexArray& getLayerTwoVertices()   const;
    const sf::VertexArray& getLayerThreeVertices() const;
    const sf::VertexArray& getLayerSixVertices()   const;
    const sf::VertexArray& getCanopyVertices()     const;
    const sf::Texture&     getTileSet()            const;

    const std::map<int, LayeredTile*>&        getLayeredMaps()        const;
    
    int getWidth()  const;
    int getHeight() const;
    
    //returns the maps music
    std::string getMusic();
    
    //returns map name
    std::string getName();
    
    //returns the map id
    int getMapID();

    virtual ~TileMap();

private:
    //fills vertex arrays with tiles that correlate to the from the build phase
	void vertexFill(std::map<int, LayeredTile*>::iterator it);
    
};

#endif /* TileMap_h */

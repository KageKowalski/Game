//Josh Seelye
#ifndef TileMap_h
#define TileMap_h

#include <stdio.h>
#include <vector>
#include <SFML/Graphics.hpp>
#include "AutoAnimation.h"
#include "TileSet.h"

class TileMap
{
    class Tile
    {
    private:
        //handles animation for tiles
        AutoAnimation _animate;
        
        //id that correlates to the position in the tilemap
        int _tileID;
        
        //current animation step
        int _step;
        
        //position of tile on the map
        sf::Vector2f _position;
        
        //function gets the correct tile animation for each tile
        AutoAnimation getTileAnimation(int ID);
    
    public:
        Tile();
        
        //constructs a tile with its correct id starts animation
        //starts the animation on step one if you want to start on another step call setAnimStep after initialization
        //sets the position on map
        Tile(int ID, const sf::Vector2f& position);
        
        //updates the animation of the tile if the current delta time is greater
        //than the set animation time
        //if the tile only has one step the function exits before accessing the vertexarray
        void updateAnimStep(sf::Time);
        
        //sets animation step to a desired animation step regardless of time
        //goes from [1 _animate.getTotalAnimSteps()]
        void setAnimStep(unsigned int step);
        
        //returns the tile Id for the current tile
        int  getID();
        
        //changes a tiles id
        void setID(int ID);
        
        //returns the current animation step
        int getAnimStep();
        
        //returns the position of the tile
        const sf::Vector2f& getPosition() const;

    };
    
private:
    //layer 1 with the background being considered layer 0
    //layer 4 and 5 are sprite sheets
    //these layers are loaded from top to bottom meaning that canopy will be displayed above ground
    Tile** _ground;
    Tile** _layerTwo;
    Tile** _layerThree;
    Tile** _layerSix;
    Tile** _canopy;
    TileSet _tileset;
    
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
    
public:
    //basic constructor
    TileMap(std::string music);
    
    //builds the map and returns true on a successful build
    //send maps with a -1 value for invalid textures
    //if a map has a -2 value in the 0 position the map will be thrown out
    bool build(int* ground, int* layerTwo, int* layerThree, int* layerSix, int* canopy, int width, int height, std::string tilesetFileName);
    
    //updates all animated tiles in the map
    void updateMap(sf::Time);
    
    //returns the vertexarrays from the corresponding layer
    const sf::VertexArray& getGroundVertices()     const;
    const sf::VertexArray& getLayerTwoVertices()   const;
    const sf::VertexArray& getLayerThreeVertices() const;
    const sf::VertexArray& getLayerSixVertices()   const;
    const sf::VertexArray& getCanopyVertices()     const;
    const sf::Texture&     getTileSet()            const;
    
    //returns the maps music
    std::string getMusic();
    
    virtual ~TileMap();

private:
    //fills vertex arrays with tiles that correlate to the from the build phase
	void vertexFill(int y, int x);
    
};

#endif /* TileMap_h */

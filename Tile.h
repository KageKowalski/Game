#ifndef Tile_hpp
#define Tile_hpp
#include <stdio.h>
#include <vector>
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <stdint.h>

#include "AutoAnimation.h"
#include "Sound.h"
#include "Sun.h"
#include "EventBus.h"
#include "Player.h"
#include "Chrono.h"
#include "Settings.h"
#include "TileSoundHandler.h"
#include "Collidable.h"

class Tile
{
private:
    //handles animation for tiles
    AutoAnimation _animate;
    
    //id that correlates to the position in the tilemap
    int _tileID;
    int _growID;
    
    //current animation step
    int _step;
    
    //function gets the correct tile animation for each tile
    AutoAnimation getTileAnimation(int ID);
    
    float _volume;
    
    //contains all tile properties in bits
    //  bit 7 is unused
    //  bit 6 is unused
    //  bit 5 is unused
    //  bit 4 is a interactable connector
    //  bit 3 is if the tile is interactable
    //  bit 2 is set if a tile radiates sound
    //  bit 1 is set when a tile has movement sound
    //  bit 0 is set if you can't walk on a tile
    uint8_t _properties;
    
    
    std::string _soundFilename;
    
public:
    Tile();
    
    //constructs a tile with its correct id starts animation
    //starts the animation on step one if you want to start on another step call setAnimStep after initialization
    //sets the position on map
    Tile(int ID, char properties = 0, std::string soundFilename = "");
    
    virtual ~Tile();
    
    //updates the animation of the tile if the current delta time is greater
    //than the set animation time
    //if the tile only has one step the function exits before accessing the vertexarray
    void update();
    
    //sets animation step to a desired animation step regardless of time
    //goes from [1 _animate.getTotalAnimSteps()]
    void setAnimStep(unsigned int step);
    
    //returns the tile Id for the current tile
    int  getID() const;
    
    //changes a tiles id
    void setID(int ID);
    
    int  getGrowID() const;
    
    //changes a tile so it 
    void setGrowID(int ID);
    
    //returns the current animation step
    int getAnimStep() const;
    
    //return properties
    uint8_t getProperties() const;
    
    //returns the sound file that this tile plays
    const std::string& getSoundFilename() const;

    
};

#endif /* Tile_hpp */

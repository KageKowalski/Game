#include "Tile.h"

Tile::Tile() : _properties(0), _tileID(-1), _step(0), _animate(AutoAnimation(0,0,0,0,sf::seconds(.3f)))
{}
Tile::Tile(int ID, char properties, std::string soundFilename) : _tileID(ID), _step(0), _animate(getTileAnimation(ID)), _properties(properties), _soundFilename(soundFilename), _growID(0)
{
    _volume = Settings::get().getEffectsVolume();
}
Tile::~Tile()
{}

//Moves the animation step forward one if the the time exceeds that last and deals with the sound
void Tile::update()
{
    if((_animate.getTotalAnimSteps() > 1))
    {
        _animate.update(Chrono::get().getDeltaTime());
        _step = _animate.getCurrAnimStep();
    }
    if(_growID != 0)
    {
        //switch(_growID)
        //{
            //case 92:
                if(Sun::get().getHour() == 5)
                {
                    _tileID = _growID;
                    _growID = 0;
                }
               // break;
        //}
    }
}
void Tile::setAnimStep(unsigned int step)
{
    if(step <= _animate.getTotalAnimSteps())
    {
        _animate.setCurrAnimStep(step);
        _step = step;
    }
}
int  Tile::getID() const    { return _tileID; }
void Tile::setID(int ID)    { _tileID = ID;   }
int  Tile::getGrowID() const{ return _growID; }
void Tile::setGrowID(int ID){ _growID = ID;   }
int  Tile::getAnimStep() const   { return _step;   }
uint8_t Tile::getProperties() const
{
    return _properties;
}
const std::string& Tile::getSoundFilename() const
{
    return _soundFilename;
}

/************************
 Tile Animation Handler
 ************************/
AutoAnimation Tile::getTileAnimation(int ID)
{
    switch(ID)
    {
        case  0:
        case  1:
        case  2:
        case  3:
        case  4:
        case  5:
        case  6:
        case  7:
        case  8:
        case  9:
        case  10:
        case  11:
        case  12:
            return AutoAnimation(0,8,16,16,sf::seconds(.3f));
            break;
            //case  :
            //  return AutoAnimation(0,3,16,16,sf::seconds(1.0f));
            //break;
        //case :
        default:
            return AutoAnimation(0,1,16,16,sf::seconds(0.0f));
            break;
    }
}

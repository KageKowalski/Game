#include "Tile.h"

Tile::Tile() : _tileID(-1), _step(0), _animate(AutoAnimation(0,0,0,0,sf::seconds(.3f)))
{}
Tile::Tile(int ID, const sf::Vector2f& postition, const float &volume, char properties, std::string soundFilename) : _tileID(ID), _step(0), _animate(getTileAnimation(ID)), _position(postition), _properties(properties), _soundFilename(soundFilename)
{
    _volume = volume;
    //transposed position for correct tile position
    //tile position is incorrect
    _centerPosition.x = _position.y * 16 + 8;
    _centerPosition.y = _position.x * 16 + 8;
}
Tile::~Tile()
{}

//Moves the animation step forward one if the the time exceeds that last and deals with the sound
void Tile::update(sf::Time deltaTime, const sf::Vector2f& pposition)
{
    if((_animate.getTotalAnimSteps() > 1))
    {
        _animate.update(deltaTime);
        _step = _animate.getCurrAnimStep();
    }
    if(_properties&0x02)
    {
        
    }
    if(_properties&0x04)
    {
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
int  Tile::getID()        { return _tileID; }
void Tile::setID(int ID)  { _tileID = ID;   }
int  Tile::getAnimStep()  { return _step;   }
const sf::Vector2f& Tile::getPosition()       const
{
    return _position;
}
const sf::Vector2f& Tile::getCenterPosition() const
{
    return _centerPosition;
}
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
        case 13:
            return AutoAnimation(0,5,16,16,sf::seconds(1.0f));
            break;
            //case  :
            //  return AutoAnimation(0,3,16,16,sf::seconds(1.0f));
            //break;
        default:
            return AutoAnimation(0,1,16,16,sf::seconds(1.0f));
            break;
    }
}

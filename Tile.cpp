#include "Tile.h"

Tile::Tile() : _properties(0), _tileID(-1), _step(0), _animate(AutoAnimation(0,0,0,0,sf::seconds(.3f)))
{}
Tile::Tile(int ID, const sf::Vector2f& postition, int mapKeyID, char properties, std::string soundFilename) : _tileID(ID), _step(0), _animate(getTileAnimation(ID)), _position(postition), _mapKeyID(mapKeyID), _properties(properties), _soundFilename(soundFilename), _growID(0)
{
    if(_properties & 0x08) EventBus::get().registerListener(Event::EventType::EV_INTERACT,    this);
    if(_properties & 0x04) EventBus::get().registerListener(Event::EventType::EV_RADIALSOUND, this);
    _volume = Settings::get().getEffectsVolume();
    _centerPosition.x = _position.x * 16 + 8;
    _centerPosition.y = _position.y * 16 + 8;
}
Tile::~Tile()
{
    if(_properties & 0x04) EventBus::get().removeListener(Event::EventType::EV_RADIALSOUND, this);
    if(_properties & 0x08) EventBus::get().removeListener(Event::EventType::EV_INTERACT, this);
}

void Tile::handleEvent(Event* const e)
{
    switch (e->getType())
    {
        case Event::EV_RADIALSOUND:
            if(std::abs(Player::get().getCenterPosition().x - _centerPosition.x) < 512 && std::abs(Player::get().getCenterPosition().y - _centerPosition.y) < 512 ) TileSoundHandler::get().attachTileSounds(_centerPosition, _properties, _soundFilename);
            break;
        case Event::EV_INTERACT:
            if(((abs(Player::get().getCenterPosition().x - _centerPosition.x) < 12 && abs(Player::get().getCenterPosition().y - _centerPosition.y) < 3) && Player::get().getDirection() == Direction::LEFT) || ((abs(_centerPosition.x - Player::get().getCenterPosition().x) < 12 && abs(Player::get().getCenterPosition().y - _centerPosition.y) < 3) && Player::get().getDirection() == Direction::RIGHT))
            {
                std::unique_ptr<Event> eventPtr;
                switch(_tileID)
                {
                    case 92:
                        std::pair<int, int> j(_tileID,_mapKeyID);
                        eventPtr = std::make_unique<InteractableConnectorEvent>(j);
                        EventBus::get().postEvent(eventPtr);
                        _growID = _tileID;
                        _tileID = -3;
                        break;
                }
            }
            break;
    }
}

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
int  Tile::getID()          { return _tileID; }
void Tile::setID(int ID)    { _tileID = ID;   }
int  Tile::getGrowID()      { return _growID; }
void Tile::setGrowID(int ID){ _growID = ID;   }
int  Tile::getAnimStep()    { return _step;   }
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
bool Tile::collision(const Collidable& obj) const
{
    
}
sf::FloatRect Tile::getGlobalBounds() const
{
    sf::FloatRect globalBounds;
    switch(_tileID)
    {
        case 92:
            break;
    }
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

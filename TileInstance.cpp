#include "TileInstance.h"

TileInstance::TileInstance()
{
    _centerPosition = sf::Vector2f(0.0f,0.0f);
    _position = sf::Vector2f(0.0f,0.0f);
    _tile = nullptr;
}

TileInstance::TileInstance(const Tile& tile, const sf::Vector2f& position) : _tile(&tile), _position(position)
{
    if(_tile->getProperties() & 0x04) EventBus::get().registerListener(Event::EventType::EV_RADIALSOUND, this);
    _centerPosition.x = _position.x + 8;
    _centerPosition.y = _position.y + 8;
}
TileInstance::~TileInstance()
{
    EventBus::get().removeListener(Event::EventType::EV_RADIALSOUND, this);
}
const sf::Vector2f& TileInstance::getPosition() const
{
    return _position;
}
const sf::Vector2f& TileInstance::getCenterPosition() const
{
    return _centerPosition;
}
const Tile* TileInstance::getTile() const
{
    return _tile;
}
void TileInstance::setPosition(const sf::Vector2f& position)
{
    _position = position;
    _centerPosition.x = _position.x + 8;
    _centerPosition.y = _position.y + 8;
}
void TileInstance::setTile(const Tile& tile)
{
    _tile = &tile;
}

bool TileInstance::collision(const Collidable& obj) const
{
    return false;
}
sf::FloatRect TileInstance::getGlobalBounds() const
{
    sf::FloatRect globalBounds;
    switch(_tile->getID())
    {
        case 92:
            globalBounds.left   = _position.x * 16.0f + 3;
            globalBounds.top    = _position.y * 16.0f;
            globalBounds.width  = 9;
            globalBounds.height = 16;
            break;
        default:
            globalBounds.left   = _position.x * 16.0f;
            globalBounds.top    = _position.y * 16.0f;
            globalBounds.width  = 16;
            globalBounds.height = 16;
            break;
    }
    return globalBounds;
}

void TileInstance::handleEvent(Event* const e)
{
    switch (e->getType())
    {
        case Event::EV_RADIALSOUND:
            if(std::abs(Player::get().getCenterPosition().x - _centerPosition.x) < 512 && std::abs(Player::get().getCenterPosition().y - _centerPosition.y) < 512 ) TileSoundHandler::get().attachTileSounds(_centerPosition, _tile->getProperties(), _tile->getSoundFilename());
            break;
    }
}

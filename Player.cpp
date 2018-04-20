// Klayton Kowalski

#include "Player.h"

Player::Player() : Character(sf::Vector2f(0.0f, 0.0f), 0, 24, 16, 32, "Player")
{
    _maxStamina = 10;
    _currStamina = 10;
    m_TextureCoords = sf::Vector2f(0.0f, 0.0f);
    m_Universal = true;
}

Player::~Player() {}


int  Player::getStamina() const
{
    return _currStamina;
}
bool Player::decrementStamina()
{
    _elapsedTimeDecrement += Chrono::get().getDeltaTime();
    if(_currStamina - 1 < 0)
    {
        return false;
    }
    if(_elapsedTimeDecrement.asSeconds() > .25)
    {
        _currStamina--;
        _elapsedTimeDecrement -= sf::seconds(0.25f);
    }
    return true;
}
bool Player::incrementStamina()
{
    if(_currStamina + 1 > _maxStamina)
    {
        return false;
    }
    _currStamina++;
    return true;
}
void Player::setStamina(int value)
{
    if(value > _maxStamina)
    {
        _currStamina = _maxStamina;
    }
    else if(value < 0)
    {
        _currStamina = 0;
    }
    else
    {
        _currStamina = value;
    }
}

void Player::update(sf::Time deltaTime)
{
    Character::update(deltaTime);
    if(m_Walking)
    {
        _elapsedTimeIncrement += Chrono::get().getDeltaTime();
        if(_currStamina == 0 && _elapsedTimeIncrement.asSeconds() > 5)
        {
            incrementStamina();
            _elapsedTimeIncrement -= sf::seconds(5.0f);
        }
        else if(_currStamina != 0 && _elapsedTimeIncrement.asSeconds() > .5)
        {
            incrementStamina();
            _elapsedTimeIncrement -= sf::seconds(0.5f);
        }
    }
}

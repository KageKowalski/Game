#include "Sun.h"

Sun::Sun()
{
    _hourChangeTime = sf::seconds(0.5f);
}

void Sun::update(sf::Time deltaTime)
{
    _elapsedTime+=deltaTime;
    if(_elapsedTime >= _hourChangeTime)
    {
        _elapsedTime -= _hourChangeTime;
        ++_hour %= 24;
    }
}
int Sun::getHour() const
{
    return _hour;
}

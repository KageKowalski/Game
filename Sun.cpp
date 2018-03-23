#include "Sun.h"

Sun::Sun()
{
    //makes a 25 minute day
    _hourChangeTime = sf::seconds(25.0f);
    _hour = 4;
    _currPos = DAWN;
}

void Sun::update(sf::Time deltaTime)
{
    _elapsedTime+=deltaTime;
    if(_elapsedTime >= _hourChangeTime)
    {
        _elapsedTime -= _hourChangeTime;
        ++_hour %= 60;
        if(_hour <= 8 && _hour >= 2)
        {
            _currPos = DAWN;
        }
        if(_hour <= 37 && _hour >= 9)
        {
            _currPos = DAYLIGHT;
        }
        if(_hour <= 44  && _hour >= 38)
        {
            _currPos = DUSK;
        }
        if((_hour <= 60 && _hour >= 45) || _hour < 2)
        {
            _currPos = NIGHT;
        }
    }
}
int Sun::getHour() const
{
    return _hour;
}
Sun::TimeOfDay Sun::getTimeOfDay() const
{
    return _currPos;
}
std::string Sun::getTimeOfDayString() const
{
    switch (_currPos) {
        case DAYLIGHT:
            return "Day";
            break;
        case NIGHT:
            return "Night";
            break;
        case DAWN:
            return "Dawn";
            break;
        case DUSK:
            return "Dusk";
            break;
    }
}

#include "Sun.h"

Sun::Sun()
{
    //makes a 25 minute day
    _hourChangeTime = sf::seconds(0.3f);
    _hour = 4;
    _currPos = TimeOfDay::DAWN;
}

void Sun::update()
{
	_elapsedTime += Chrono::get().getDeltaTime();
    if(_elapsedTime >= _hourChangeTime)
    {
        _elapsedTime -= _hourChangeTime;
        ++_hour %= 60;
        if(_hour <= 8 && _hour >= 2)
        {
			_currPos = TimeOfDay::DAWN;
        }
        if(_hour <= 37 && _hour >= 9)
        {
            _currPos = TimeOfDay::DAYLIGHT;
        }
        if(_hour <= 44  && _hour >= 38)
        {
            _currPos = TimeOfDay::DUSK;
        }
        if((_hour <= 60 && _hour >= 45) || _hour < 2)
        {
            _currPos = TimeOfDay::NIGHT;
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
	case TimeOfDay::DAYLIGHT:
		return "Day";
		break;
	case TimeOfDay::NIGHT:
		return "Night";
		break;
	case TimeOfDay::DAWN:
		return "Dawn";
		break;
	case TimeOfDay::DUSK:
		return "Dusk";
		break;
	}
}

#ifndef Sun_hpp
#define Sun_hpp

#include <SFML/System.hpp>

class Sun
{
public:
    enum TimeOfDay
    {
        DAYLIGHT,
        DUSK,
        DAWN,
        NIGHT
    };
    void update(sf::Time deltaTime);
    int getHour() const;
    TimeOfDay getTimeOfDay() const;
    std::string getTimeOfDayString() const;
private:
    Sun();
public:
    Sun(Sun const&)             = delete;
    void operator=(Sun const&)  = delete;
    
    static Sun& get()
    {
        static    Sun instance;
        return        instance;
    }
private:
    int                _hour;
    sf::Time    _elapsedTime;
    sf::Time _hourChangeTime;
    TimeOfDay       _currPos;
    
};

#endif

#ifndef Sun_hpp
#define Sun_hpp

#include <SFML/System.hpp>

class Sun
{
public:
    void update(sf::Time deltaTime);
    int getHour() const;
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
    
};

#endif

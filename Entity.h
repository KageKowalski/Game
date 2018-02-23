//Josh Seelye
#ifndef Entity_hpp
#define Entity_hpp

#include <string>
#include <SFML/Graphics.hpp>

class Entity
{
protected:
    std::string  _name;
    bool     _movement;
    sf::Sprite _sprite;
    
public:
    Entity() = delete;
    Entity(std::string name);
    
    bool getMovement();
    
    std::string getName();
    void setName(std::string name);
};

#endif

//Josh Seelye
#include "Entity.h"

Entity::Entity(std::string name)
{
    _name = name;
}

bool Entity::getMovement()
{
    return _movement;
}

std::string Entity::getName()
{
    return _name;
}


void Entity::setName(std::string name)
{
    _name = name;
}

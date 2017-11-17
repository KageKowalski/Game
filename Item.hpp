#ifndef Item_h
#define Item_h

#include "Entity.hpp"
#include "Player.hpp"

class Item : public Entity
{
public:
    Item(){}
    
    Item(string _name)
    {
        name = _name;
    }
    
    bool operator==(const Item& rhs)
    {
        return (name == rhs.name);
    }
};

#endif /* Item_h */

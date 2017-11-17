
#ifndef Interactable_h
#define Interactable_h

#include "Entity.hpp"
#include "Monster.hpp"
#include "Player.hpp"

class Interactable : public Entity
{
private:
    string desc;
    Monster monster;
    int trapDamage
    
public:
    //constructor for trap iteractable
    Interactable(string _desc, int _trapDamage) : desc(_desc), trapDamage(_trapDamage)
    {}
    //constructor for a monster interact
    Interactable(string _desc, Monster _monster) : desc(_desc), monster(_monster)
    {}
    
    void interact()
    {
        if(trapDamage)
    }
};

#endif /* Interactable_h */

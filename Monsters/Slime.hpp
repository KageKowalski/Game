#ifndef Slime_h
#define Slime_h

#include "../Monster.hpp"
#include "../Equipments/TrashSet/TrashSet.h"

class Slime : public Monster
{

//public functions
public:
    Slime(int _level, string _name = "Slime") : Monster(_name,6,2,0,5,3,5,6)
    {
        level = _level;
        for(int i = 0; i < level; i++) levelIncrease();
    }

//private Functions
private:
    void levelIncrease()
    {
        level_up(30, hp, RANDOM_GENERATOR.nextInt(3)+1, 25);
        level_up(30, hp, RANDOM_GENERATOR.nextInt(3)+1, 25);
        level_up(30, hp, RANDOM_GENERATOR.nextInt(3)+1, 25);
        setLoot();
    }
    
    void setLoot()
    {
        loot.add(Equipment(), 70);
        loot.add(WornLadle(level), 10);
        loot.add(RustyPot(level), 10);
        loot.add(CardboardBox(level), 10);
        loot.add(TrashBag(level), 10);
        loot.add(DiscardedCrocs(level), 10);
        loot.add(TornMittens(level), 10);
        loot.add(BrokenBoard(level), 10);
    }
    
};


#endif /* Slime_h */

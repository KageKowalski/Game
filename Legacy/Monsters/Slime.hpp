#ifndef Slime_h
#define Slime_h

#include "../Monster.hpp"
#include "../Equipments/TrashSet/TrashSet.h"

class Slime : public Monster
{

//public functions
public:
    Slime(int _level, string _name = "Slime") : Monster(_name,_level,6,2,0,5,3,5,6)
    {
        for(int i = 0; i < 3*(level-1); i++)
        {
            levelIncrease();
        }
        setLoot();
    }

//private Functions
private:
    void levelIncrease()
    {
        int key = RANDOM_GENERATOR.nextInt(3)+1;
        switch (key) {
            case 1:
                level_up(100, hp, RANDOM_GENERATOR.nextInt(3)+1, 40);
                break;
            case 2:
                level_up(100, str, RANDOM_GENERATOR.nextInt(1)+1, 10);
                break;
            case 3:
                level_up(100, lck, RANDOM_GENERATOR.nextInt(2)+1, 30);
                break;
            case 4:
                level_up(100, spd, RANDOM_GENERATOR.nextInt(2)+1, 30);
        }
    }
    
    void setLoot()
    {
        loot.add(Equipment(), 40);
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

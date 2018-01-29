//
//  Zombie.hpp
//  Game
//
//  Created by Joshua Seelye on 11/17/17.
//  Copyright © 2017 Josh Seelye. All rights reserved.
//

#ifndef Zombie_h
#define Zombie_h


#include "../Monster.hpp"
#include "../Equipments/TrashSet/*"

class Zombie : public Monster
{
//public functions
public:
    Zombie(int _level, string _name = "Zombie") : level(_level), Monster(_name,7,7,3,2,2,3,8)
    {
        levelIncrease();
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
        loot.add(Equipment(), 70)
        loot.add(WornLadle(level), 10)
        loot.add(RustyPot.hpp(level), 10)
        loot.add(CardboardBox(level), 10)
        loot.add(TrashBag(level), 10)
        loot.add(DiscardedCrocs(level), 10)
        loot.add(TornMittens(level), 10)
        loot.add(BrokenBoard(level), 10)
    }
    
    

#endif /* Zombie_h */

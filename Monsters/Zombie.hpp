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
    //private variables
private:
    int level;
    DiscreteDistribution<int> levelChanges;
    
    //public functions
public:
    Slime(int _level, string _name = "Zombie") : level(_level)
    {
        Monster(_name,7,3,3,2,2,3,8);
        levelIncrease();
    }
    
    //private Functions
private:
    void levelIncrease()
    {
        gold+=5*(level);
        exp+=3*level;
        if(level>1)
        {
            levelChanges.add(1, 25);
            levelChanges.add(2, 40);
            levelChanges.add(3, 35);
            levelChanges.add(4, 0);
            for(int statsToIncrease = 3*(level - 1);statsToIncrease!=-1;statsToIncrease--)
            {
                int roll = levelChanges();
                switch(roll)
                {
                    case 1:
                        hp+=5;
                        break;
                    case 2:
                        str++;
                        break;
                    case 3:
                        def++;
                        break;
                    case 4:
                        lck++;
                        break;
                }
            }
        }
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

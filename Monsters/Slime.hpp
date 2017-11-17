#ifndef Slime_h
#define Slime_h

#include "../Monster.hpp"
#include "../Equipments/TrashSet/*"

class Slime : public Monster
{
//private variables
private:
    int level;
    DiscreteDistribution<int> levelChanges;

//public functions
public:
    Slime(int _level, string _name = "Slime") : level(_level)
    {
        Monster(_name,6,2,0,5,3,5,6);
        levelIncrease();
    }

//private Functions
private:
    void levelIncrease()
    {
        gold+=5*(level/5);
        exp+=2*level;
        if(level>1)
        {
            levelChanges.add(1, 45);
            levelChanges.add(2, 25);
            levelChanges.add(3, 10);
            levelChanges.add(4, 20);
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
    
    
    
};


#endif /* Slime_h */

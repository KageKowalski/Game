
#ifndef Slime_h
#define Slime_h

#include "Monster.hpp"

class Slime : public Monster
{
//private variables
private:
    unsigned int level;
    DiscreteDistribution<int> levelChanges;

//public functions
public:
    Slime(int _level, string _name = "Slime" ) : level(_level)
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
        if(level < 10)
        {
            Item nothing = Item("Nothing");
            Equipment eq1 = Equipment("Rusted Pot",0,0,1,0,0,false);
            Equipment eq2 = Equipment("Slimy Dagger",0,1,0,0,0,false);
            Equipment eq3 = Equipment("Slime Boots",4,0,0,0,0,false);
            loot.add(nothing, 60);
            loot.add(eq1, 17);
            loot.add(eq2, 18);
            loot.add(eq3, 10);
        }
    }
    
    
    
};


#endif /* Slime_h */

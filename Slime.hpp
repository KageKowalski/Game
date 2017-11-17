
#ifndef Slime_h
#define Slime_h

#include "Monster.hpp"

class Slime : public Monster
{
private:
    int level;
    DiscreteDistribution<int> levelChanges;
public:
    Slime(int _level, string _name = "Slime" ) : level(_level)
    {
        Monster(_name,6,2,0,5,3,5,6,//loot);
        levelIncrease();
    }
    
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
    }
};


#endif /* Slime_h */

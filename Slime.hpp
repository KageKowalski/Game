
#ifndef Slime_h
#define Slime_h

#include "Monster.hpp"

class Slime : public Monster
{
private:
    int level;
    int DiscreteDistribution<int> levelChanges;
public:
    Slime(string _name, int _level) : name(_name), level(_level)
    {
        hp  = 6;
        str = 2;
        def = 0;
        lck = 5;
        spd = 3;
        gold = 5;
        exp = 6;
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
            for(int statsToIncrease = 3*(level - 1);statsToIncrase!=-1;statsToIncrease--)
            {
                roll = levelChanges();
                switch roll
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
                    luck++;
                    break;
                }
            }
        }
    }
}


#endif /* Slime_h */

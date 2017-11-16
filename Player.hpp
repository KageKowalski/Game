//Contains all setters and getters for a player: Level and exp
//also has a inventory that can cycle

#ifndef Player_h
#define Player_h

#include "Combatant.hpp"
#include "Inventory.hpp"


class Player : public Combatant
{
//private instance variables
private:
    Inventory inv;
    int level;
    int pp;
    //discrete distributions only returns 1 or 0 based on if you crit/dodged
    DiscreteDistribution<bool> crit;
    DiscreteDistribution<bool> dodge;

//public Functions
public:
    int getLevel()          { return level;  }
    
    int getPp()             { return pp;     }
    
    void setPp(int x)       { pp += x;       }
    
    bool rollCrit()         { updateCrit();  return crit();  }
    
    bool rollDodge()        { updateDodge(); return dodge(); }
    
    double getCritPercent()
    {
        updateCrit();
        return crit.probability(1);
    }
    
    double getDodge()
    {
        updateDodge();
        return dodge.probability(1);
    }
    
    int attack(Combatant& mo)
    {
        if(rollCrit())
        {
            mo.setHp(-((2*str-mo.getDef())>0?(2*str-mo.getDef()):1));
            return (2*str-mo.getDef())>0?(2*str-mo.getDef()):1;
        }
        mo.setHp(-((str-mo.getDef())>0?(str-mo.getDef()):1));
        return (str-mo.getDef())>0?(str-mo.getDef()):1;
    }
  
//  (room location?) death() { go to location of start of game and delete }
    
    //returns true if leveled up
    bool increaseExp(int x)
    {
        exp+=x;
        if(exp>=nextLevel())
        {
            levelUp();
            return true;
        }
        return false;
    }
    
    int nextLevel() { return (int)round(sqrt((double)(20*level))); }
    
//private functions
private:
    
    void updateCrit()
    {
        crit.add(false, 100-lck);
        crit.add(true, lck);
    }
    
    void updateDodge()
    {
        dodge.add(false, 230-lck-spd);
        dodge.add(true, lck+spd);
    }
    
    void levelUp()
    {
        exp = (exp - nextLevel());
        level++;
    }
    
    
    
//singleton design pattern for player class
private:
    Player()
    {
        inv = Inventory();
        level = 1;
        hp  = 10;
        str = 1;
        def = 0;
        lck = 0;
        spd = 0;
        pp  = 5;
        gold = 0;
        exp = 0;
    }
public:
    Player(Player const&)          = delete;
    void operator=(Player const&)  = delete;
    
    static Player& get()
    {
        static Player   instance;
        return          instance;
    }
};

#endif /* Player_h */

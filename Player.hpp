//Contains all setters and getters for a player: Level and exp
//also has a inventory that can cycle

#ifndef Player_h
#define Player_h

#include "Combatant.hpp"
#include "Inventory.hpp"
#include "Monster.hpp"

class Player : public Combatant
{
//private instance variables
private:
    Inventory inv;
    int level;
    DiscreteDistribution<int> crit;

//public Functions
public:
    int getLevel()          { return level; }
    
    double getCritPercent()
    {
        updateCrit();
        return crit.probability(1);
    }
    
    int attack(Monster& mo)
    {
        int roll = crit();
        if(roll == 1){ return (2*str-mo.getDef())>0?(2*str-mo.getDef()):1; }
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
    
//private functions
private:
    int nextLevel() { return (int)round(sqrt((double)(20*level))); }
    
    void updateCrit()
    {
        crit.add(0, 100-lck);
        crit.add(1, lck);
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

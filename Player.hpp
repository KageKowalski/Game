//Contains all setters and getters for basic character
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

//public Functions
public:
    int getLevel()  { return level; }
    
    int getExp()    { return exp;   }
    
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
    int nextLevel(){ return (int)round(sqrt((double)(20*level))); }
    
    void levelUp()
    {
        exp = 0 + (exp - nextLevel());
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

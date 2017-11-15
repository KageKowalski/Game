//
//  Player.hpp
//  GameFirstDraft
//
//  Created by Joshua Seelye on 11/13/17.
//  Copyright © 2017 Josh Seelye. All rights reserved.
//

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
    
    int getHp()     { return hp;    }
    
    int getPp()     { return pp;    }
    
    int getStr()    { return str;   }
    
    int getDef()    { return def;   }
    
    int getLck()    { return lck;   }
    
    int getSpd()    { return spd;   }
    
    void setHp(int x)     { hp+=x;  }
    
    void setPp(int x)     { pp+=x;  }
    
    void setStr(int x)    { str+=x; }
    
    void setDef(int x)    { def+=x; }
    
    void setLck(int x)    { lck+=x; }
    
    void setSpd(int x)    { spd+=x; }
    
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
    int nextLevel()
    {
        return (int)round(sqrt((double)(20*level)));
    }
    
    void levelUp()
    {
        
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

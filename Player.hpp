//Contains all setters and getters for a player: Level and exp
//also has a inventory that can cycle
/**********************************
 getLevel
 getPp
 setPp
 rollCrit - returns true if crit
 getCritPercent - returns percentage of crit chance
 attack - returns damage done
 increaseExp - returns true if you leveled
 nextLevel - returns total required exp to level at players level
 **********************************/

#ifndef Player_h
#define Player_h

#include "Combatant.hpp"
#include "Inventory.hpp"
#include "Equipments/StarterSet/StarterSet.hpp"

class Player : public Combatant
{
//private instance variables
private:
    Inventory inv;
    unsigned int level;
    int pp;
    Equipment helmet;
    Equipment vest;
    Equipment boots;
    Equipment pants;
    Equipment gloves;
    Equipment oneHanded;
    Equipment shield;
    Equipment twoHanded;

//public Functions
public:
    unsigned int getLevel() { return level;      }
    int getPp()             { return pp;         }
    void setPp(int x)       { pp += x;           }
    
    bool set_helm(Equipment eq)
    {
        if(eq.get_EquipType() == EquipType::HELMET) { helmet = eq; return true;   }
        return false;
    }
    bool set_vest(Equipment eq)
    {
        if(eq.get_EquipType() == EquipType::VEST)   { vest = eq; return true;   }
        return false;
    }
    bool set_gloves(Equipment eq)
    {
        if(eq.get_EquipType() == EquipType::GLOVES) { gloves = eq; return true; }
        return false;
    }
    bool set_pants(Equipment eq)
    {
        if(eq.get_EquipType() == EquipType::PANTS)  { pants = eq; return true;  }
        return false;
    }
    bool set_weapon(Equipment eq)
    {
        //need to fix for shield
        if(eq.get_EquipType() == EquipType::ONE_HANDED)
        {
            oneHanded = eq;
            return true;
        }
        //need to fix for shield
        if(eq.get_EquipType() == EquipType::TWO_HANDED)
        {
            twoHanded = eq;
            return true;
        }
        return false;
    }
    
    pair<int, bool> attack(Combatant& mo)
    {
        pair<int, bool> ret;
        if(rollCrit())
        {
            mo.setHp(-((2*str-mo.getDef())>0?(2*str-mo.getDef()):1));
            ret.first = (2*str-mo.getDef())>0?(2*str-mo.getDef()):1;
            ret.second = true;
            return ret;
        }
        mo.setHp(-((str-mo.getDef())>0?(str-mo.getDef()):1));
        ret.first = (str-mo.getDef())>0?(str-mo.getDef()):1;
        ret.second = false;
        return ret;
    }
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
    
    int nextLevel() { return 15+pow(level+1,2); }
    
//private functions
private:
    
    //recursive level up
    void levelUp()
    {
        exp = (exp - nextLevel());
        level++;
        if(exp>=nextLevel())
        {
            levelUp();
        }
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
        helmet = Hair();
        vest   = Shirt();
        pants  = Pants();
        gloves = Hands();
        boots  = Shoes();
        shield = Arm();
        oneHanded = Fists();
        twoHanded = Nothing();
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

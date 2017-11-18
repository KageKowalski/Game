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
    
    bool set_helm(Equipment eq);
    bool set_vest(Equipment eq);
    bool set_gloves(Equipment eq);
    bool set_pants(Equipment eq);
    bool set_weapon(Equipment eq);
    
    int get_hp_boost();
    int get_str_boost();
    int get_def_boost();
    int get_lck_boost();
    int get_spd_boost();

    pair<int, bool> attack(Combatant& mo);
    
    //returns true if leveled up
    bool increaseExp(int x);
    
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

bool Player::set_helm(Equipment eq)
{
    if(eq.get_EquipType() == EquipType::HELMET) { helmet = eq; return true;   }
    return false;
}
bool Player::set_vest(Equipment eq)
{
    if(eq.get_EquipType() == EquipType::VEST)   { vest = eq; return true;   }
    return false;
}
bool Player::set_gloves(Equipment eq)
{
    if(eq.get_EquipType() == EquipType::GLOVES) { gloves = eq; return true; }
    return false;
}
bool Player::set_pants(Equipment eq)
{
    if(eq.get_EquipType() == EquipType::PANTS)  { pants = eq; return true;  }
    return false;
}
bool Player::set_weapon(Equipment eq)
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

pair<int, bool> Player::attack(Combatant& mo)
{
    pair<int, bool> ret;
    if(rollCrit())
    {
        mo.setHp(-((2*str+-mo.getDef())>0?(2*str-mo.getDef()):1));
        ret.first = (2*str-mo.getDef())>0?(2*str-mo.getDef()):1;
        ret.second = true;
        return ret;
    }
    mo.setHp(-((str-mo.getDef())>0?(str-mo.getDef()):1));
    ret.first = (str-mo.getDef())>0?(str-mo.getDef()):1;
    ret.second = false;
    return ret;
}

bool Player::increaseExp(int x)
{
    exp+=x;
    if(exp>=nextLevel())
    {
        levelUp();
        return true;
    }
    return false;
}

int Player::get_hp_boost()
{
    return (helmet.get_hp()+vest.get_hp()+gloves.get_hp()+boots.get_hp()+pants.get_hp()+shield.get_hp()+oneHanded.get_hp()+ twoHanded.get_hp());
}
int Player::get_str_boost()
{
    return (helmet.get_str()+vest.get_str()+gloves.get_str()+boots.get_str()+pants.get_str()+shield.get_str()+oneHanded.get_str()+ twoHanded.get_str());
}
int Player::get_def_boost()
{
    return (helmet.get_def()+vest.get_def()+gloves.get_def()+boots.get_def()+pants.get_def()+shield.get_def()+oneHanded.get_def()+ twoHanded.get_def());
}
int Player::get_lck_boost()
{
    return (helmet.get_lck()+vest.get_lck()+gloves.get_lck()+boots.get_lck()+pants.get_lck()+shield.get_lck()+oneHanded.get_lck()+ twoHanded.get_lck());
}
int Player::get_spd_boost()
{
    return (helmet.get_spd()+vest.get_spd()+gloves.get_spd()+boots.get_spd()+pants.get_spd()+shield.get_spd()+oneHanded.get_spd()+ twoHanded.get_spd());
}

#endif /* Player_h */

#ifndef Player_h
#define Player_h

#include "Combatant.hpp"
#include "Inventory.hpp"
#include "Equipments/StarterSet/StarterSet.h"

class Player : public Combatant
{
//private instance variables
private:
    Inventory inv;
    unsigned int level;
    int pp;
    
    int hp_eq;
    int str_eq;
    int def_eq;
    int lck_eq;
    int spd_eq;
    
    int cur_hp;
    int cur_pp;
    
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
    
    void max_heal()         { cur_hp = hp_eq; }
    int change_cur_hp(int s);
    int get_cur_hp()        { return cur_hp;  }
    
    void max_pprestore()    { cur_pp = pp; }
    int change_cur_pp(int s);
    int get_cur_pp()        { return cur_pp;  }
    
    
    int get_hp_boost();
    int get_str_boost();
    int get_def_boost();
    int get_lck_boost();
    int get_spd_boost();
    
    int get_hp_tot()    { return hp_eq;  }
    int get_str_tot()   { return str_eq; }
    int get_def_tot()   { return def_eq; }
    int get_lck_tot()   { return lck_eq; }
    int get_spd_tot()   { return spd_eq; }

    pair<int, bool> attack(Combatant& mo);
    
    bool isDead(){ return cur_hp <= 0; }
    
    //returns amount of times leveled up
    int increaseExp(int x);
    
    //return at what xp you will reach next level
    int nextLevel() { return 15+pow(level+1,2); }
    
    void equip(Equipment& eq);
    
//private functions
private:
    
    bool set_helm(Equipment& eq);
    bool set_vest(Equipment& eq);
    bool set_gloves(Equipment& eq);
    bool set_boots(Equipment& eq);
    bool set_pants(Equipment& eq);
    bool set_weapon(Equipment& eq);
    bool set_shield(Equipment& eq);
    
    //recursive level up
    int levelUp(int amnt)
    {
        exp = (exp - nextLevel());
        level++;
        if(exp>=nextLevel())
        {
            amnt = levelUp(amnt+1);
        }
        return amnt;
    }
    void update_stats()
    {
        hp_eq  = hp + get_hp_boost();
        if(hp_eq < cur_hp){cur_hp = hp_eq;}
        str_eq = str + get_str_boost();
        def_eq = def + get_def_boost();
        lck_eq = lck + get_lck_boost();
        spd_eq = spd + get_spd_boost();
    }
//singleton design pattern for player class
private:
    Player()
    {
        inv = Inventory();
        level = 1;
        hp  = 10;
        cur_hp = hp;
        str = 1;
        def = 0;
        lck = 0;
        spd = 0;
        pp  = 5;
        gold = 0;
        exp = 0;
        update_stats();
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

bool Player::set_helm(Equipment& eq)
{
    if(eq.get_equipType() == EquipType::HELMET) { helmet = eq; update_stats(); return true;   }
    return false;
}
bool Player::set_vest(Equipment& eq)
{
    if(eq.get_equipType() == EquipType::VEST)   { vest = eq; update_stats(); return true;   }
    return false;
}
bool Player::set_gloves(Equipment& eq)
{
    if(eq.get_equipType() == EquipType::GLOVES) { gloves = eq; update_stats(); return true; }
    return false;
}
bool Player::set_pants(Equipment& eq)
{
    if(eq.get_equipType() == EquipType::PANTS)  { pants = eq; update_stats(); return true;  }
    return false;
}
bool Player::set_boots(Equipment& eq)
{
    if(eq.get_equipType() == EquipType::BOOTS)  { boots = eq; update_stats(); return true;  }
    return false;
}
bool Player::set_weapon(Equipment& eq)
{
    //need to fix for shield
    if(eq.get_equipType() == EquipType::ONE_HANDED)
    {
        oneHanded = eq;
        update_stats();
        return true;
    }
    //need to fix for shield
    if(eq.get_equipType() == EquipType::TWO_HANDED)
    {
        twoHanded = eq;
        update_stats();
        return true;
    }
    return false;
}
bool Player::set_shield(Equipment& eq)
{
    //fix for one handed
    return false;
}

pair<int, bool> Player::attack(Combatant& mo)
{
    pair<int, bool> ret;
    if(rollCrit())
    {
        mo.setHp(-((2*str_eq-mo.getDef())>0?(2*str_eq-mo.getDef()):1));
        ret.first = (2*str_eq-mo.getDef())>0?(2*str_eq-mo.getDef()):1;
        ret.second = true;
        return ret;
    }
    mo.setHp(-((str_eq-mo.getDef())>0?(str_eq-mo.getDef()):1));
    ret.first = (str_eq-mo.getDef())>0?(str_eq-mo.getDef()):1;
    ret.second = false;
    return ret;
}

int Player::increaseExp(int x)
{
    exp+=x;
    if(exp>=nextLevel())
    {
        int amnt = levelUp(0);
        return 1 + amnt;
    }
    return 0;
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

int Player::change_cur_hp(int s)
{
    if(cur_hp + s > hp_eq)
    {
        int temp = hp_eq - cur_hp;
        cur_hp = hp_eq;
        return temp;
    }
    cur_hp+=s;
    return s;
}

int Player::change_cur_pp(int s)
{
    if(cur_pp + s > pp)
    {
        int temp = pp - cur_pp;
        cur_pp = pp;
        return temp;
    }
    cur_pp+=s;
    return s;

}

void Player::equip(Equipment& eq)
{
    if(set_helm(eq)){}
    else if(set_vest(eq)){}
    else if(set_gloves(eq)){}
    else if(set_boots(eq)){}
    else if(set_pants(eq)){}
    else if(set_weapon(eq)){}
    else if(set_shield(eq)){}
}

#endif /* Player_h */

#ifndef Equipment2_h
#define Equipment2_h

#include "Item.hpp"

enum class EquipsType {
    HELMET,
    VEST,
    PANTS,
    BOOTS,
    GLOVES,
    ONE_HANDED,
    TWO_HANDED,
    SHIELD,
    NONE
};


class Equipment2 : public Item
{
public:
    //  An object of type Equipment will never be constructed for serious use.
    //  This constructor is merely to assist sub-classes' constructors.
    Equipment2(string _name="Nothing", EquipsType _equipsType=EquipsType::NONE)
    {
        name      = _name;
        lvl       = 0;
        hp        = 0;
        pp        = 0;
        str       = 0;
        def       = 0;
        spd       = 0;
        lck       = 0;
        equipsType = _equipsType;
    }
    
    //  GETTERS
    string get_name()          { return name;      }
    int get_lvl()              { return lvl;       }
    int get_hp()               { return hp;        }
    int get_pp()               { return pp;        }
    int get_str()              { return str;       }
    int get_def()              { return def;       }
    int get_spd()              { return spd;       }
    int get_lck()              { return lck;       }
    EquipsType get_equipsType()  { return equipsType; }
    
    //  Overloads == operator for comparing Equipments.
    bool operator==(const Equipment2& rhs) { return lvl == rhs.lvl && hp == rhs.hp && pp == rhs.pp && str == rhs.str && def == rhs.def
        && spd == rhs.spd && lck == rhs.lck && equipsType == rhs.equipsType && name == rhs.name;    }
    
    //  Levels up this Equipment.
    void level_up(int percent, int& stat, int secondRoll)
    {
        DiscreteDistribution<bool> second_roll;
        second_roll.add(false, 100-secondRoll);
        second_roll.add(true, secondRoll);
        levelChanges.add(false, 100-percent);
        levelChanges.add(true, percent);
        if(levelChanges())
        {
            stat++;
            if(second_roll())
            {
                level_up(percent, stat, secondRoll);
            }
        }
    }
    
protected:
    int lvl;
    int hp;
    int pp;
    int str;
    int def;
    int spd;
    int lck;
    EquipsType equipsType;
    DiscreteDistribution<bool> levelChanges;
};

#endif /* Equipment_h */


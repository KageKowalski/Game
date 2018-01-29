#ifndef Equipment_h
#define Equipment_h

#include "Item.hpp"

enum class EquipType {
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


class Equipment : public Item
{
public:
	//  An object of type Equipment will never be constructed for serious use.
	//  This constructor is merely to assist sub-classes' constructors.
    Equipment(string _name="Nothing", EquipType _equipType=EquipType::NONE)
    {
        name      = _name;
		lvl       = 0;
        hp        = 0;
		pp        = 0;
        str       = 0;
        def       = 0;
        spd       = 0;
        lck       = 0;
		equipType = _equipType;
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
	EquipType get_equipType()  { return equipType; }
    

	//  Overloads == operator for comparing Equipments.
    bool operator==(const Equipment& rhs) { return lvl == rhs.lvl && hp == rhs.hp && pp == rhs.pp && str == rhs.str && def == rhs.def
											&& spd == rhs.spd && lck == rhs.lck && equipType == rhs.equipType && name == rhs.name;    }
    
    const Equipment& operator=(const Equipment& rhs);
    
    virtual void increase_lvl(){}
    
    string toString();

protected:
	int lvl;
    int hp;
	int pp;
    int str;
    int def;
	int spd;
    int lck;
	EquipType equipType;
    
    //  Levels up this Equipment.
    void level_up(int percent, int& stat, int amount, int secondRoll);
};

void Equipment::level_up(int percent, int& stat, int amount, int secondRoll)
{
    DiscreteDistribution<int> levelChanges;
    DiscreteDistribution<int> second_roll;
    second_roll.add(0, 100-secondRoll);
    second_roll.add(1, secondRoll);
    levelChanges.add(0, 100-percent);
    levelChanges.add(1, percent);
    if(levelChanges())
    {
        stat+=amount;
        if(second_roll())
        {
            level_up(percent, stat, amount, secondRoll-1);
        }
    }
}

const Equipment& Equipment::operator=(const Equipment& rhs)
{
    this->name = rhs.name;
    this->hp   = rhs.hp;
    this->def  = rhs.def;
    this->lck  = rhs.lck;
    this->spd  = rhs.spd;
    this->lvl  = rhs.lvl;
    this->pp   = rhs.pp;
    this->equipType = rhs.equipType;
    return *this;
}

string Equipment::toString()
{
    ostringstream oss;
    oss << "Hp: " << hp << " Str: " << str << " Def: " << def << " Luk: " << lck << " Spd: " << spd << " PP: " << pp << endl;
    return oss.str();
}

#endif /* Equipment_h */

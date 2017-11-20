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


	//  Levels up this Equipment.
    void level_up(int percent, int& stat, int amount, int secondRoll);
    void level_up(int _hp, int _str, int _def, int _spd, int _lck, int _nhp, int _nstr, int _ndef, int _nspd, int _nlck, int _pp);
    
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
	DiscreteDistribution<int> levelChanges;
};

void Equipment::level_up(int percent, int& stat, int amount, int secondRoll)
{
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

void Equipment::level_up(int _hp, int _str, int _def, int _spd, int _lck, int _nhp, int _nstr, int _ndef, int _nspd, int _nlck, int _pp=0){
    int n;
    
    n = _hp/100;
    _hp = _hp%100;
    for(int i = 0; i < n; i++){
        if(_hp > RANDOM_GENERATOR.nextInt(100)) hp+=RANDOM_GENERATOR.nextInt(3)+1;
    }
    
    n = _str/100;
    _str = _str%100;
    for(int i = 0; i < n; i++){
        if(_str > RANDOM_GENERATOR.nextInt(100)) str++;
    }
    
    n = _def/100;
    _def = _def%100;
    for(int i = 0; i < n; i++){
        if(_def > RANDOM_GENERATOR.nextInt(100)) def++;
    }
    
    n = _spd/100;
    _spd = _spd%100;
    for(int i = 0; i < n; i++){
        if(_spd > RANDOM_GENERATOR.nextInt(100)) spd++;
    }
    
    n = _lck/100;
    _lck = _lck%100;
    for(int i = 0; i < n; i++){
        if(_lck > RANDOM_GENERATOR.nextInt(100)) lck++;
    }
    
    n = _nhp/100;
    _nhp = _nhp%100;
    for(int i = 0; i < n; i++){
        if(_nhp > RANDOM_GENERATOR.nextInt(100)) hp-=RANDOM_GENERATOR.nextInt(3)+1;
    }
    
    n = _nstr/100;
    _nstr = _nstr%100;
    for(int i = 0; i < n; i++){
        if(_nstr > RANDOM_GENERATOR.nextInt(100)) str--;
    }
    
    n = _ndef/100;
    _ndef = _ndef%100;
    for(int i = 0; i < n; i++){
        if(_ndef > RANDOM_GENERATOR.nextInt(100)) def--;
    }
    
    n = _nspd/100;
    _nspd = _nspd%100;
    for(int i = 0; i < n; i++){
        if(_nspd > RANDOM_GENERATOR.nextInt(100)) spd--;
    }
    
    n = _nlck/100;
    _nlck = _lck%100;
    for(int i = 0; i < n; i++){
        if(_nlck > RANDOM_GENERATOR.nextInt(100)) lck--;
    }
    
    n = _pp/100;
    _pp = _pp%100;
    for(int i = 0; i < n; i++){
        if(_pp > RANDOM_GENERATOR.nextInt(100)) pp++;
    }
    
    lvl++;
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
    this->levelChanges = rhs.levelChanges;
    return *this;
}

string Equipment::toString()
{
    ostringstream oss;
    oss << "Hp: " << hp << " Str: " << str << " Def: " << def << " Luk: " << lck << " Spd: " << spd << " PP: " << pp << endl;
    return oss.str();
}

#endif /* Equipment_h */

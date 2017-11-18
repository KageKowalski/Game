#ifndef Monster_h
#define Monster_h

#include "Combatant.hpp"

class Monster : public Combatant
{
public:
    Monster(string _name, int _hp, int _str, int _def, int _lck, int _spd, int _gold, int _exp, DiscreteDistribution<Item> _loot = DiscreteDistribution<Item>())
    {
        name = _name;
        hp   = _hp;
        str  = _str;
        def  = _def;
        lck  = _lck;
        spd  = _spd;
        gold = _gold;
        exp  = _exp;
        loot = _loot;
    }
protected:
    Monster(){}
    DiscreteDistribution<Item> loot;
    
    Item get_loot(){ return loot(); }
    
};

#endif /* Monster_h */

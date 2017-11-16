
#ifndef StandardMob_h
#define StandardMob_h

#include "Monster.hpp"

class StandardMob : public Monster
{
public:
    StandardMob(int _hp, int _str, int _def, int _lck, int _spd, int _gold, int _exp, DiscreteDistribution<Item>& _loot)
    {
        hp   = _hp;
        str  = _str;
        def  = _def;
        lck  = _lck;
        spd  = _spd;
        gold = _gold;
        exp  = _exp;
        loot = _loot;
    }
};

#endif /* StandardMob_h */

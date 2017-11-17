//
//  Monster.hpp
//  GameFirstDraft
//
//  Created by Joshua Seelye on 11/13/17.
//  Copyright © 2017 Josh Seelye. All rights reserved.
//

#ifndef Monster_h
#define Monster_h
#include "Player.hpp"

class Monster : public Combatant
{
public:
    Monster(string _name, int _hp, int _str, int _def, int _lck, int _spd, int _gold, int _exp, DiscreteDistribution<Item>& _loot)
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
    DiscreteDistribution<Item> loot;
    
    
    Item death()
    {
        return loot();
    }
};

#endif /* Monster_h */

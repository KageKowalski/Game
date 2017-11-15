//
//  Monster.hpp
//  GameFirstDraft
//
//  Created by Joshua Seelye on 11/13/17.
//  Copyright © 2017 Josh Seelye. All rights reserved.
//

#ifndef Monster_h
#define Monster_h
#include "Combatant.hpp"

class Monster : public Combatant
{
public:
    Monster(int _hp, int _str, int _def, int _lck, int _spd, int _gold, int _exp)
    {
        hp   = _hp;
        str  = _str;
        def  = _def;
        lck  = _lck;
        spd  = _spd;
        gold = _gold;
        exp  = _exp;
    }
};

#endif /* Monster_h */

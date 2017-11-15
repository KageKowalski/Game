//
//  Character.hpp
//  GameFirstDraft
//
//  Created by Joshua Seelye on 11/13/17.
//  Copyright © 2017 Josh Seelye. All rights reserved.
//

#ifndef Character_h
#define Character_h

#include "Entity.hpp"

class Combatant : public Entity
{
protected:
    int hp;
    int pp;
    int spd;
    int str;
    int def;
    int lck;
    int gold;
    int exp;
};

#endif /* Character_h */

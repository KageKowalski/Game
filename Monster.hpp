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
protected:
    DiscreteDistribution<Item> loot;
    
    Item death()
    {
        return loot();
    }
};

#endif /* Monster_h */

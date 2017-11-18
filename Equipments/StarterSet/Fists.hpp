//
//  Fists.hpp
//  Game
//
//  Created by Joshua Seelye on 11/17/17.
//  Copyright © 2017 Josh Seelye. All rights reserved.
//

#ifndef Fists_h
#define Fists_h

#include "../../Equipment.hpp"

class  Fists : public Equipment{
public:
    Fists(){ Equipment("Fists", EquipType::ONE_HANDED); }
};

#endif /* Fists_h */

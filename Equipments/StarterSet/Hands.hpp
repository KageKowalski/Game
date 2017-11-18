//
//  Hands.hpp
//  Game
//
//  Created by Joshua Seelye on 11/17/17.
//  Copyright © 2017 Josh Seelye. All rights reserved.
//

#ifndef Hands_h
#define Hands_h

#include "../../Equipment.hpp"

class Hands : public Equipment{
public:
    Hands(){ Equipment("Hands", EquipType::GLOVES); }
};

#endif /* Hands_h */

//
//  Pants.hpp
//  Game
//
//  Created by Joshua Seelye on 11/17/17.
//  Copyright © 2017 Josh Seelye. All rights reserved.
//

#ifndef Pants_h
#define Pants_h

#include "../../Equipment.hpp"

class  Pants : public Equipment{
public:
    Pants(){ Equipment("Pants", EquipType::PANTS); }
};

#endif /* Pants_h */

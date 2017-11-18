//
//  Shirt.hpp
//  Game
//
//  Created by Joshua Seelye on 11/17/17.
//  Copyright © 2017 Josh Seelye. All rights reserved.
//

#ifndef Shirt_h
#define Shirt_h

#include "../../Equipment.hpp"

class  Shirt : public Equipment{
public:
    Shirt(){ Equipment("Shirt", EquipType::VEST); }
};

#endif /* Shirt_h */

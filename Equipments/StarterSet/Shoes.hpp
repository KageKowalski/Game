//
//  Shoes.hpp
//  Game
//
//  Created by Joshua Seelye on 11/17/17.
//  Copyright © 2017 Josh Seelye. All rights reserved.
//

#ifndef Shoes_h
#define Shoes_h

#include "../../Equipment.hpp"

class  Shoes : public Equipment{
public:
    Shoes(){ Equipment("Shoes", EquipType::BOOTS); }
};

#endif /* Shoes_h */

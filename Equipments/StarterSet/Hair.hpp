//
//  Hair.hpp
//  Game
//
//  Created by Joshua Seelye on 11/17/17.
//  Copyright © 2017 Josh Seelye. All rights reserved.
//

#ifndef Hair_h
#define Hair_h

#include "../../Equipment.hpp"

class  Hair : public Equipment{
public:
    Hair(){ Equipment("Hair", EquipType::HELMET); }
};

#endif /* Hair_h */

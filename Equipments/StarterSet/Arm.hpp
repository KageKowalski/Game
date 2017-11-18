//
//  Arm.hpp
//  Game
//
//  Created by Joshua Seelye on 11/17/17.
//  Copyright © 2017 Josh Seelye. All rights reserved.
//

#ifndef Arm_h
#define Arm_h

#include "../../Equipment.hpp"

class  Arm : public Equipment{
public:
    Arm(){ Equipment("Arm", EquipType::SHIELD); }
};

#endif /* Arm_h */

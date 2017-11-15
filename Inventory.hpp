//
//  Inventory.hpp
//  GameFirstDraft
//
//  Created by Joshua Seelye on 11/13/17.
//  Copyright © 2017 Josh Seelye. All rights reserved.
//

#ifndef Inventory_h
#define Inventory_h

#include <list>
#include "StatModifiers.hpp"

class Inventory
{
private:
    std::list<StatModifiers> inv;
    int maxSize;
    int currentSize;
public:
    Inventory() : maxSize(3), currentSize(0), inv(0)
    {}
};

#endif /* Inventory_h */

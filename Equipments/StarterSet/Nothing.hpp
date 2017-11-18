//
//  Nothing.hpp
//  Game
//
//  Created by Joshua Seelye on 11/17/17.
//  Copyright © 2017 Josh Seelye. All rights reserved.
//

#ifndef Nothing_h
#define Nothing_h

class Nothing : public Equipment{
public:
    Nothing(){ Equipment("Nothing", EquipType::TWO_HANDED); }
};

#endif /* Nothing_h */

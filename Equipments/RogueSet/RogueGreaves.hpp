#ifndef RogueGreaves_h
#define RogueGreaves_h

#include "../../Equipment.hpp"
//  Stat increase per level: 0.93

class RogueGreaves : public Equipment{
public:
    RogueGreaves(int);
    void increase_lvl();
};

RogueGreaves::RogueGreaves(int _lvl)
{
    Equipment("Serrated Dirk", EquipType::ONE_HANDED);
    for(int i = _lvl; i != -1; i--){ increase_lvl(); }
}
void RogueGreaves::increase_lvl()
{
    level_up(30, spd, 1, 30);
    level_up(20, def, 1, 10);
    level_up(15, lck, 1, 10);
    level_up(7, hp, RANDOM_GENERATOR.nextInt(3)+1, 12);
}

#endif /* RogueGreaves_h */

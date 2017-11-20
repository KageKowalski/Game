#ifndef RogueHood_h
#define RogueHood_h

#include "../../Equipment.hpp"

//  Stat increase per level: 0.93

class RogueHood : public Equipment{
public:
    RogueHood(int);
    void increase_lvl();
};

RogueHood::RogueHood(int _lvl)
{
    Equipment();
    name = "Rogue Hood";
    equipType = EquipType::HELMET;
    for(int i = _lvl; i != -1; i--){ increase_lvl(); }
}
void RogueHood::increase_lvl()
{
    level_up(30, spd, 1, 30);
    level_up(20, def, 1, 10);
    level_up(15, lck, 1, 10);
    level_up(7, hp, RANDOM_GENERATOR.nextInt(3)+1, 12);
}

#endif /* RogueHood_h */

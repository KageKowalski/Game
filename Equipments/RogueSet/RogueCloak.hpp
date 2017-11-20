#ifndef RogueCloak_h
#define RogueCloak_h

#include "../../Equipment.hpp"
//  Stat increase per level: 0.93

class RogueCloak : public Equipment{
public:
    RogueCloak(int);
    void increase_lvl();
};

RogueCloak::RogueCloak(int _lvl)
{
    Equipment();
    name = "Rogue Cloak";
    equipType = EquipType::VEST;
    for(int i = _lvl; i != -1; i--){ increase_lvl(); }
}
void RogueCloak::increase_lvl()
{
    level_up(30, spd, 1, 30);
    level_up(20, def, 1, 10);
    level_up(15, lck, 1, 10);
    level_up(7, hp, RANDOM_GENERATOR.nextInt(3)+1, 12);
}

#endif /* RogueCloak_h */

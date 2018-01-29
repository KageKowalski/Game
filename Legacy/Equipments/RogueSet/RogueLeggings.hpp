#ifndef RogueLeggings_h
#define RogueLeggings_h

#include "../../Equipment.hpp"

//  Stat increase per level: 0.93

class RogueLeggings : public Equipment{
public:
    RogueLeggings(int);
    void increase_lvl();
};

RogueLeggings::RogueLeggings(int _lvl)
{
    name = "Rogue Leggings";
    equipType = EquipType::PANTS;
    for(int i = _lvl; i != 0; i--){ increase_lvl(); }
}
void RogueLeggings::increase_lvl()
{
    level_up(30, spd, 1, 30);
    level_up(20, def, 1, 10);
    level_up(15, lck, 1, 10);
    level_up(7, hp, RANDOM_GENERATOR.nextInt(3)+1, 12);
}


#endif /* RogueLeggings_h */

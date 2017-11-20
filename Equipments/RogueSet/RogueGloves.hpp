#ifndef RogueGloves_h
#define RogueGloves_h

#include "../../Equipment.hpp"
//  Stat increase per level: 0.93

class RogueGloves : public Equipment{
public:
    RogueGloves(int);
    void increase_lvl();
};

RogueGloves::RogueGloves(int _lvl)
{
    Equipment();
    name = "Rogue Gloves";
    equipType = EquipType::GLOVES;
    for(int i = _lvl; i != -1; i--){ increase_lvl(); }
}
void RogueGloves::increase_lvl()
{
    level_up(30, spd, 1, 30);
    level_up(20, def, 1, 10);
    level_up(15, lck, 1, 10);
    level_up(7, hp, RANDOM_GENERATOR.nextInt(3)+1, 12);
}

#endif /* RogueGloves_h */

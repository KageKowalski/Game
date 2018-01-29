
#ifndef SerratedDirk_h
#define SerratedDirk_h

#include "../../Equipment.hpp"

//  Stat increase per level: 1.09

class SerratedDirk : public Equipment{
public:
    SerratedDirk(int);
    void increase_lvl();
};

SerratedDirk::SerratedDirk(int _lvl)
{
    pp = 3;
    name = "Serrated Dirk";
    equipType = EquipType::ONE_HANDED;
    for(int i = _lvl; i != 0; i--){ increase_lvl(); }
}
void SerratedDirk::increase_lvl()
{
    level_up(40, str, 1, 12);
    level_up(3, def, 1, 30);
    level_up(10, lck, 1, 10);
    level_up(15, spd, 1, 10);
    level_up(7, hp, RANDOM_GENERATOR.nextInt(3)+1, 12);
}



#endif /* SerratedDirk_h */

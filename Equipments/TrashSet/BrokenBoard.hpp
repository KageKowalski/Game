#ifndef BrokenBoard_h
#define BrokenBoard_h

#include "../../Equipment.hpp"

//  Average Stats/Level: .15

class BrokenBoard : public Equipment {
public:
    BrokenBoard(int level){
        name = "Broken Board";
        equipType = EquipType::SHIELD;
        for(int i = 0; i < level; i++) increase_lvl();
    }
    void increase_lvl()
    {
        level_up(15, str, 1, 25);
        level_up(35, def, 1, 25);
        level_up(15, lck, 1, 10);
        level_up(10, hp, -(RANDOM_GENERATOR.nextInt(3)), 10);
        level_up(10, str, -1, 25);
        level_up(35, def, -1, 25);
        level_up(15, lck, -1, 10);
        level_up(15, spd, -1, 10);
        level_up(30, pp, 1, 0);
    }
};

#endif /* BrokenBoard_h */

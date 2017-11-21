#ifndef WornLadle_h
#define WornLadle_h

#include "../../Equipment.hpp"

//  Average Stats/Level: .2
//  Average pp/Level:    .1

class WornLadle : public Equipment {
public:
    WornLadle(int level){
        name = "Worn Ladle";
        equipType = EquipType::ONE_HANDED;
        for(int i = 0; i < level; i++) increase_lvl();
    }
    void increase_lvl()
    {
        level_up(30, str, 1, 25);
        level_up(30, str, 1, 25);
        level_up(5 , def, 1, 25);
        level_up(5 , lck, 1, 10);
        level_up(10, hp, -(RANDOM_GENERATOR.nextInt(3)), 10);
        level_up(10, str, -1, 25);
        level_up(10, def, 1, 25);
        level_up(10, lck, 1, 10);
        level_up(10, spd, 1, 10);
    }
};

#endif /* WornLadle_h */

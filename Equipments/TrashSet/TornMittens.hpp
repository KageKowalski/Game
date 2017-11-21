#ifndef TornMittens_h
#define TornMittens_h

#include "../../Equipment.hpp"

// Average Stats/Level: .15

class TornMittens : public Equipment {
public:
    TornMittens(int level){
        name = "Torn Mittens";
        equipType = EquipType::GLOVES;
        for(int i = 0; i < level; i++) increase_lvl();
    }
    void increase_lvl()
    {
        level_up(5 , str, 1, 25);
        level_up(20, def, 1, 25);
        level_up(15, lck, 1, 10);
        level_up(25, spd, 1, 10);
        level_up(10, hp, -(RANDOM_GENERATOR.nextInt(3)), 20);
        level_up(10, str, -1, 25);
        level_up(10, def, -1, 25);
        level_up(10, lck, -1, 10);
        level_up(10, spd, -1, 10);
    }
};

#endif /* TornMittens_h */

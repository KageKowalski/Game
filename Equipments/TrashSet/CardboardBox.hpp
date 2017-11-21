#ifndef CardboardBox_h
#define CardboardBox_h

#include "../../Equipment.hpp"

//  Average Stats/Level: .15

class CardboardBox : public Equipment {
public:
    CardboardBox(int level){
        name = "Cardboard Box";
        equipType = EquipType::VEST;
        for(int i = 0; i < level; i++) increase_lvl();
    }
    void increase_lvl()
    {
        level_up(10, hp, (RANDOM_GENERATOR.nextInt(3)+1), 10);
        level_up(30, def, 1, 25);
        level_up(5, lck, 1, 25);
        level_up(20, spd, 1, 10);
        level_up(10, hp, -(RANDOM_GENERATOR.nextInt(3)+1), 10);
        level_up(10, str, -1, 25);
        level_up(5, def, -1, 25);
        level_up(15, lck, -1, 10);
        level_up(15, spd, -1, 10);
        level_up(7, hp, RANDOM_GENERATOR.nextInt(3)+1, 12);
    }
};

#endif /* X_h */

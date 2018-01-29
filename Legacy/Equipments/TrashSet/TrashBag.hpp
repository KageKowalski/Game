#ifndef TrashBag_h
#define TrashBag_h

#include "../../Equipment.hpp"

//  Average Stats/Level: .15

class TrashBag : public Equipment {
public:
    TrashBag(int level){
        name = "Trash Bag";
        equipType = EquipType::PANTS;
        for(int i = 0; i < level; i++) increase_lvl();
    }
    void increase_lvl()
    {
        level_up(20, def, 1, 25);
        level_up(20, spd, 2, 10);
        level_up(10, hp, -(RANDOM_GENERATOR.nextInt(3)), 10);
        level_up(10, str, -1, 25);
        level_up(10, def, -1, 25);
        level_up(10, lck, -1, 10);
        level_up(10, spd, -1, 10);
        level_up(5, hp, RANDOM_GENERATOR.nextInt(3)+1, 12);
    }
};

#endif /* TrashBag_h */

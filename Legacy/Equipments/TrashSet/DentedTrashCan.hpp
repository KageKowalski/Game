#ifndef DentedTrashCan_h
#define DentedTrashCan_h

#include "../../Equipment.hpp"

//  Average Stats/Level: .35
//  Average pp/Level:    .17

class DentedTrashCan : public Equipment {
public:
    DentedTrashCan(int level){
        name = "Dented Trash Can";
        equipType = EquipType::TWO_HANDED;
        for(int i = 0; i < level; i++) increase_lvl();
    }
    void increase_lvl()
    {
        level_up(40, str, 1, 25);
        level_up(5, def, 1, 25);
        level_up(10, hp, -(RANDOM_GENERATOR.nextInt(3)), 10);
        level_up(10, str, -1, 25);
        level_up(10, def, -1, 25);
        level_up(15, lck, -1, 10);
        level_up(15, spd, -1, 10);
        level_up(17, pp, 1, 0);
    }
};

#endif /* DentedTrashCan_h */

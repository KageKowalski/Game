#ifndef DiscardedCrocs_h
#define DiscardedCrocs_h

#include "../../Equipment.hpp"

//  Average Stats/Level: .15

class DiscardedCrocs : public Equipment {
public:
    DiscardedCrocs(int level){
        Equipment("Discarded Crocs", EquipType::BOOTS);
        name = "Discarded Crocs";
        equipType = EquipType::BOOTS;
        for(int i = 0; i < level; i++) increase_lvl();
    }
    void increase_lvl()
    {
        level_up(10, def, 1, 25);
        level_up(30, lck, 1, 25);
        level_up(25, spd, 1, 10);
        level_up(10, hp, -(RANDOM_GENERATOR.nextInt(3)), 10);
        level_up(10, str, -1, 25);
        level_up(10, def, -1, 25);
        level_up(10, lck, -1, 10);
        level_up(10, spd, -1, 10);
        level_up(10, pp, 1, 12);
    }
};

#endif /* DiscardedCrocs_h */

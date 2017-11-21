#ifndef RustyPot_h
#define RustyPot_h

#include "../../Equipment.hpp"

//  Average Stats/Level: .15

class RustyPot : public Equipment {
public:
    RustyPot(int level);

    void increase_lvl()
    {
        level_up(5, str, 1, 25);
        level_up(40, def, 1, 20);
        level_up(20, spd, 1, 10);
        level_up(10, hp, -(RANDOM_GENERATOR.nextInt(3)), 10);
        level_up(10, str, -1, 25);
        level_up(10, def, -1, 25);
        level_up(10, lck, -1, 10);
        level_up(10, spd, -1, 10);
        level_up(10, pp, 1, 12);
    }
};

RustyPot::RustyPot(int level){
    name = "Rusty Pot";
    equipType = EquipType::HELMET;
	for(int i = 0; i < level; i++) increase_lvl();
}

#endif /* RustyPot_h */

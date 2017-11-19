#ifndef RustyPot_h
#define RustyPot_h

#include "../../Equipment.hpp"

//  Average Stats/Level: .15

class RustyPot : public Equipment {
	public:
		RustyPot(int level);
};

RustyPot::RustyPot(int level){
	Equipment("Rusty Pot", EquipType::HELMET);
	for(int i = 0; i < level; i++) level_up(0, 105, 140, 0, 120, 110, 110, 110, 110, 110);
}

#endif /* RustyPot_h */

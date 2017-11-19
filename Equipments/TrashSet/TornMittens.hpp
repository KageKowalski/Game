#ifndef TornMittens_h
#define TornMittens_h

#include "../../Equipment.hpp"

// Average Stats/Level: .15

class TornMittens : public Equipment {
	public:
		TornMittens(int level){
			Equipment("Torn Mittens", EquipType::GLOVES);
			for(int i = 0; i < level; i++) level_up(0, 105, 120, 115, 125, 110, 110, 110, 110, 110);
		}
};

#endif /* TornMittens_h */

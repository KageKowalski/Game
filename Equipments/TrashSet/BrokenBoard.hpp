#ifndef BrokenBoard_h
#define BrokenBoard_h

#include "../../Equipment.hpp"

//  Average Stats/Level: .15

class BrokenBoard : public Equipment {
	public:
		BrokenBoard(int level){
            name = "Broken Board";
            equipType = EquipType::SHIELD;
			for(int i = 0; i < level; i++) level_up(0, 115, 135, 115, 0, 110, 110, 110, 110, 110);
		}
};

#endif /* BrokenBoard_h */

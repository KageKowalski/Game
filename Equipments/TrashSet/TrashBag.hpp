#ifndef TrashBag_h
#define TrashBag_h

#include "../../Equipment.hpp"

//  Average Stats/Level: .15

class TrashBag : public Equipment {
	public:
		TrashBag(int level){
			Equipment("Trash Bag", EquipType::PANTS);
			for(int i = 0; i < level; i++) level_up(105, 0, 120, 0, 220, 110, 110, 110, 110, 110);
		}
};

#endif /* TrashBag_h */

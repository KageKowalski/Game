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
			for(int i = 0; i < level; i++) level_up(0, 240, 105, 0, 0, 110, 110, 110, 110, 110, 117);
		}
};

#endif /* DentedTrashCan_h */

#ifndef DiscardedCrocs_h
#define DiscardedCrocs_h

#include "../../Equipment.hpp"

//  Average Stats/Level: .15

class DiscardedCrocs : public Equipment {
	public:
		DiscardedCrocs(int level){
			Equipment("Discarded Crocs", EquipType::BOOTS);
			for(int i = 0; i < level; i++) level_up(0, 0, 110, 130, 125, 110, 110, 110, 110, 110);
		}
};

#endif /* DiscardedCrocs_h */

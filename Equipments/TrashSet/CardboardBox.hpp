#ifndef CardboardBox_h
#define CardboardBox_h

#include "../../Equipment.hpp"

//  Average Stats/Level: .15

class CardboardBox : public Equipment {
	public:
		CardboardBox(int level){
			Equipment("Cardboard Box", EquipType::VEST);
			for(int i = 0; i < level; i++) level_up(110, 0, 130, 105, 120, 110, 110, 110, 110, 110);
		}
};

#endif /* X_h */

#ifndef WornLadle_h
#define WornLadle_h

#include "../../Equipment.hpp"

//  Average Stats/Level: .2
//  Average pp/Level:    .1

class WornLadle : public Equipment {
	public:
		WornLadle(int level){
            name = "Worn Ladle";
            equipType = EquipType::ONE_HANDED;
			for(int i = 0; i < level; i++) level_up(0, 230, 0, 105, 105, 110, 110, 110, 110, 110, 110);
		}
};

#endif /* WornLadle_h */

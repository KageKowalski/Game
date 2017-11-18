#ifndef TrashBag_h
#define TrashBag_h

#include "../../Equipment.hpp"

//  Stat increase per level: 0.3

class TrashBag : public Equipment{
	public:
		TrashBag(int);
		void level_up();
};

TrashBag::TrashBag(int _lvl){
	Equipment("Trash Bag", EquipType::PANTS);

	levelChanges.add(0, 50);
	levelChanges.add(1, 2);
	levelChanges.add(2, 2);
	levelChanges.add(3, 2);
	levelChanges.add(4, 2);
	levelChanges.add(5, 2);
	levelChanges.add(6, 35);
	levelChanges.add(7, 5);

	for(int i = 0; i < _lvl; i++) level_up();
}

void TrashBag::level_up(){
	int roll = levelChanges();

	switch(roll){
		case 1:
			hp--;
			break;
		case 2:
			str--;
			break;
		case 3:
			def--;
			break;
		case 4:
			spd--;
			break;
		case 5:
			lck--;
			break;
		case 6:
			def++;
			break;
		case 7:
			lck++;
	}

	lvl++;
}

#endif /* TrashBag_h */

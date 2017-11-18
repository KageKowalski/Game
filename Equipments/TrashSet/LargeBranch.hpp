#ifndef LargeBranch_h
#define LargeBranch_h

#include "../../Equipment.hpp"

//  Stat increase per level: .45
//  pp increase per level:   .1

class LargeBranch : public Equipment{
	public:
		LargeBranch(int);
		void level_up();
};

LargeBranch::LargeBranch(int _lvl){
	Equipment("Large Branch", EquipType::TWO_HANDED);

	levelChanges.add(0, 40);
	levelChanges.add(1, 2);
	levelChanges.add(2, 2);
	levelChanges.add(3, 2);
	levelChanges.add(4, 2);
	levelChanges.add(5, 2);
	levelChanges.add(6, 20);
	levelChanges.add(7, 15);
	levelChanges.add(8, 10);
	levelChanges.add(9, 5);

	for(int i = 0; i < _lvl; i++) level_up();
}

void LargeBranch::level_up(){
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
			str++;
			break;
		case 7:
			str+=2;
			break;
		case 8:
			pp++;
			break;
		case 9:
			lck++;
	}

	lvl++;
}

#endif /* LargeBranch */

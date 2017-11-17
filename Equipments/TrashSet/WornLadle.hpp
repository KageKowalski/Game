#include "../../Equipment.hpp"

class WornLadle : public Equipment{
	public:
		WornLadle(int);
		void level_up();
};

WornLadle::WornLadle(int _lvl){
	Equipment("Worn Ladle", EquipType::ONE_HANDED);

	levelChanges.add(0, 40);
	levelChanges.add(1, 2);
	levelChanges.add(2, 2);
	levelChanges.add(3, 2);
	levelChanges.add(4, 2);
	levelChanges.add(5, 2);
	levelChanges.add(6, 35);
	levelChanges.add(7, 10);
	levelChanges.add(8, 5);

	for(int i = 0; i < _lvl; i++) level_up();
}

void WornLadle::level_up(){
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
			pp++;
			break;
		case 8:
			luck;
	}

	lvl++;
}

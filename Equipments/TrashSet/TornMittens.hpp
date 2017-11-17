#include "../../Equipment.hpp"

class TornMittens : public Equipment{
	public:
		TornMittens(int);
		void level_up();
};

TornMittens::TornMittens(int _lvl){
	Equipment("TornMittens", EquipType::GLOVES);

	levelChanges.add(0, 50);
	levelChanges.add(1, 2);
	levelChanges.add(2, 2);
	levelChanges.add(3, 2);
	levelChanges.add(4, 2);
	levelChanges.add(5, 2);
	levelChanges.add(6, 25);
	levelChanges.add(7, 10);
	levelChanges.add(8, 5);

	for(int i = 0; i < _lvl; i++) level_up();
}

void TornMittens::level_up(){
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
			lck++;
			break;
		case 7:
			def++;
			break;
		case 8:
			str++;
	}

	lvl++;
}

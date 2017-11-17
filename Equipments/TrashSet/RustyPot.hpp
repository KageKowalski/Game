#include "../../Equipment.hpp"

class RustyPot : public Equipment{
	public:
		RustyPot(int);
		void level_up();
};

RustyPot::RustyPot(int _lvl){
	Equipment("Rusty Pot", EquipType::HELMET);

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

void RustyPot::level_up(){
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

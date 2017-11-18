#ifndef example_h
#define example_h

#include "Kage_New_Equipment_Implementation.hpp"

class ExampleHelmet : public Equipment {
	public:
		ExampleHelmet(int level);
};

ExampleHelmet::ExampleHelmet(int level){
	Equipment("Example Helmet", EquipType::HELMET);
	for(int i = 0; i < level; i++) level_up(0, 0, 115, 105, 105, 0, 105, 0, 0, 0, 0);
}

#endif /* example_h */

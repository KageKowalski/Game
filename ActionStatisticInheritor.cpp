// Kage Kowalski

#include "ActionStatisticInheritor.h"

//
//
//		CONSTANTS
//
//

const int ActionStatisticInheritor::MAX_STAT_VAL = 100;
const int ActionStatisticInheritor::MIN_STAT_VAL = 0;

//
//
//		GETTER FUNCTIONS (BASE)
//
//

int ActionStatisticInheritor::get_base_health()		{ return base_health; }
int ActionStatisticInheritor::get_base_stamina()	{ return base_stamina; }
int ActionStatisticInheritor::get_base_strength()	{ return base_strength; }
int ActionStatisticInheritor::get_base_resistance()	{ return base_resistance; }
int ActionStatisticInheritor::get_base_dexterity()	{ return base_dexterity; }
int ActionStatisticInheritor::get_base_agility()	{ return base_agility; }
int ActionStatisticInheritor::get_base_charisma()	{ return base_charisma; }
int ActionStatisticInheritor::get_base_intellect()	{ return base_intellect; }

//
//
//		GETTER FUNCTIONS (CURRENT)
//
//

int ActionStatisticInheritor::get_current_health()		{ return current_health; }
int ActionStatisticInheritor::get_current_stamina()		{ return current_stamina; }
int ActionStatisticInheritor::get_current_strength()	{ return current_strength; }
int ActionStatisticInheritor::get_current_resistance()	{ return current_resistance; }
int ActionStatisticInheritor::get_current_dexterity()	{ return current_dexterity; }
int ActionStatisticInheritor::get_current_agility()		{ return current_agility; }
int ActionStatisticInheritor::get_current_charisma()	{ return current_charisma; }
int ActionStatisticInheritor::get_current_intellect()	{ return current_intellect; }

//
//
//		CHANGE FUNCTIONS (BASE)
//
//

int ActionStatisticInheritor::increment_base_health() {
	if (base_health < MAX_STAT_VAL) {
		return base_health += 5;
	}
	else {
		Log::get().print("increment_base_health() overflow error");
		return -1;
	}
}

int ActionStatisticInheritor::increment_base_stamina() {
	if (base_stamina < MAX_STAT_VAL) {
		return base_stamina += 5;
	}
	else {
		Log::get().print("increment_base_stamina() overflow error");
		return -1;
	}
}

int ActionStatisticInheritor::increment_base_strength() {
	if (base_strength < MAX_STAT_VAL) {
		return ++base_strength;
	}
	else {
		Log::get().print("increment_base_strength() overflow error");
		return -1;
	}
}

int ActionStatisticInheritor::increment_base_resistance() {
	if (base_resistance < MAX_STAT_VAL) {
		return ++base_resistance;
	}
	else {
		Log::get().print("increment_base_resistance() overflow error");
		return -1;
	}
}

int ActionStatisticInheritor::increment_base_dexterity() {
	if (base_dexterity < MAX_STAT_VAL) {
		return ++base_dexterity;
	}
	else {
		Log::get().print("increment_base_dexterity() overflow error");
		return -1;
	}
}

int ActionStatisticInheritor::increment_base_agility() {
	if (base_agility < MAX_STAT_VAL) {
		return ++base_agility;
	}
	else {
		Log::get().print("increment_base_agility() overflow error");
		return -1;
	}
}

int ActionStatisticInheritor::increment_base_charisma() {
	if (base_charisma < MAX_STAT_VAL) {
		return ++base_charisma;
	}
	else {
		Log::get().print("increment_base_charisma() overflow error");
		return -1;
	}
}

int ActionStatisticInheritor::increment_base_intellect() {
	if (base_intellect < MAX_STAT_VAL) {
		return ++base_intellect;
	}
	else {
		Log::get().print("increment_base_intellect() overflow error");
		return -1;
	}
}

int ActionStatisticInheritor::decrement_base_health() {
	if (base_health > MIN_STAT_VAL) {
		return base_health -= 5;
	}
	else {
		Log::get().print("decrement_base_health() overflow error");
		return -1;
	}
}

int ActionStatisticInheritor::decrement_base_stamina() {
	if (base_stamina > MIN_STAT_VAL) {
		return base_stamina -= 5;
	}
	else {
		Log::get().print("decrement_base_stamina() overflow error");
		return -1;
	}
}

int ActionStatisticInheritor::decrement_base_strength() {
	if (base_strength > MIN_STAT_VAL) {
		return --base_strength;
	}
	else {
		Log::get().print("decrement_base_strength() overflow error");
		return -1;
	}
}

int ActionStatisticInheritor::decrement_base_resistance() {
	if (base_resistance > MIN_STAT_VAL) {
		return --base_resistance;
	}
	else {
		Log::get().print("decrement_base_resistance() overflow error");
		return -1;
	}
}

int ActionStatisticInheritor::decrement_base_dexterity() {
	if (base_dexterity > MIN_STAT_VAL) {
		return --base_dexterity;
	}
	else {
		Log::get().print("decrement_base_dexterity() overflow error");
		return -1;
	}
}

int ActionStatisticInheritor::decrement_base_agility() {
	if (base_agility > MIN_STAT_VAL) {
		return --base_agility;
	}
	else {
		Log::get().print("decrement_base_agility() overflow error");
		return -1;
	}
}

int ActionStatisticInheritor::decrement_base_charisma() {
	if (base_charisma > MIN_STAT_VAL) {
		return --base_charisma;
	}
	else {
		Log::get().print("decrement_base_charisma() overflow error");
		return -1;
	}
}

int ActionStatisticInheritor::decrement_base_intellect() {
	if (base_intellect > MIN_STAT_VAL) {
		return --base_intellect;
	}
	else {
		Log::get().print("decrement_base_intellect() overflow error");
		return -1;
	}
}

//
//
//		CHANGE FUNCTIONS (CURRENT)
//
//

int ActionStatisticInheritor::change_current_health(int value) {
	if (value > 0) {
		if (value + current_health > base_health) {
			return current_health = base_health;
		}
		else {
			return current_health += value;
		}
	}
	if (value < 0) {
		if (value + current_health < MIN_STAT_VAL) {
			return current_health = MIN_STAT_VAL;
		}
		else {
			return current_health += value;
		}
	}
}

//
//
//		CHANGE FUNCTIONS (CURRENT) (CONTINUED 1)
//
//

int ActionStatisticInheritor::increment_current_stamina() {
	if (current_stamina < base_stamina) {
		return ++current_stamina;
	}
	else {
		return current_stamina;
	}
}

int ActionStatisticInheritor::decrement_current_stamina() {
	if (current_stamina > MIN_STAT_VAL) {
		return --current_stamina;
	}
	else {
		return current_stamina;
	}
}

//
//
//		CHANGE FUNCTIONS (CURRENT) (CONTINUED 2)
//
//

int change_current_strength(int value, sf::Time changeTime, sf::Time activeTime) {
	
}

int change_current_resistance(int value, sf::Time changeTime, sf::Time activeTime) {

}

int change_current_dexterity(int value, sf::Time changeTime, sf::Time activeTime) {

}

int change_current_agility(int value, sf::Time changeTime, sf::Time activeTime) {
	
}

int change_current_charisma(int value, sf::Time changeTime, sf::Time activeTime) {

}

int change_current_intellect(int value, sf::Time changeTime, sf::Time activeTime) {

}
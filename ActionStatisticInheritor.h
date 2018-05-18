// Kage Kowalski

#ifndef ACTIONSTATISTICINHERITOR_H
#define ACTIONSTATISTICINHERITOR_H

#include <SFML/System/Time.hpp>
#include "Chrono.h"
#include "Log.h"

class ActionStatisticInheritor {
private:
	// Constants
	static const int MAX_STAT_VAL;
	static const int MIN_STAT_VAL;

	// Action Statistics (base)
	int base_health;
	int base_stamina;
	int base_strength;
	int base_resistance;
	int base_dexterity;
	int base_agility;
	int base_charisma;
	int base_intellect;

	// Action Statistics (current)
	int current_health;
	int current_stamina;
	int current_strength;
	int current_resistance;
	int current_dexterity;
	int current_agility;
	int current_charisma;
	int current_intellect;

public:
	// Getter Functions (base)
	// Return value of designated base Action Statistic
	int get_base_health();
	int get_base_stamina();
	int get_base_strength();
	int get_base_resistance();
	int get_base_dexterity();
	int get_base_agility();
	int get_base_charisma();
	int get_base_intellect();

	// Getter Functions (current)
	// Return value of designated current Action Statistic
	int get_current_health();
	int get_current_stamina();
	int get_current_strength();
	int get_current_resistance();
	int get_current_dexterity();
	int get_current_agility();
	int get_current_charisma();
	int get_current_intellect();

	// Change Functions (base)
	// Increment or decrement designated base Action Statistic
	// Return the updated designated base Action Statistic if successful, else -1
	int increment_base_health();
	int increment_base_stamina();
	int increment_base_strength();
	int increment_base_resistance();
	int increment_base_dexterity();
	int increment_base_agility();
	int increment_base_charisma();
	int increment_base_intellect();

	int decrement_base_health();
	int decrement_base_stamina();
	int decrement_base_strength();
	int decrement_base_resistance();
	int decrement_base_dexterity();
	int decrement_base_agility();
	int decrement_base_charisma();
	int decrement_base_intellect();

	// Change Functions (current)
	// Add value to designated current Action Statistic
	// Return the updated designated current Action Statistic
	int change_current_health(int value);

	// Change Functions (current) (continued 1)
	// Increment or decrement designated current Action Statistic
	// Return the updated designated current Action Statistic
	int increment_current_stamina();
	int decrement_current_stamina();

	// Change Functions (current) (continued 2)
	// Add value to designated current Action Statistic
	// The adding of the value occurs over changeTime time, and the completed change lasts for activeTime time
	// Return the updated designated current Action Statistic
	int change_current_strength(int value, sf::Time changeTime, sf::Time activeTime);
	int change_current_resistance(int value, sf::Time changeTime, sf::Time activeTime);
	int change_current_dexterity(int value, sf::Time changeTime, sf::Time activeTime);
	int change_current_agility(int value, sf::Time changeTime, sf::Time activeTime);
	int change_current_charisma(int value, sf::Time changeTime, sf::Time activeTime);
	int change_current_intellect(int value, sf::Time changeTime, sf::Time activeTime);
};

#endif
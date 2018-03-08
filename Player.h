// Klayton Kowalski

#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"

class Player : public Character {

public:

	Player(const sf::Vector2f position, int initAnimStep, unsigned int totalAnimSteps, unsigned int frameWidth,
		unsigned int frameHeight, const sf::String& name = "DEFAULT NAME");
	~Player();

};

#endif
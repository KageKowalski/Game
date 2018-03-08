#ifndef NPC_H
#define NPC_H

#include "Character.h"

class NPC : public Character {

public:

	NPC(const sf::Vector2f position, int initAnimStep, unsigned int totalAnimSteps, unsigned int frameWidth,
		unsigned int frameHeight, const sf::String& name = "DEFAULT NAME");
	~NPC();

protected:



};

#endif
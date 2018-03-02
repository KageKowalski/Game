// Klayton Kowalski

#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"

class Player : public Character {

public:

	Player(const sf::Vector2f position, int initAnimStep, unsigned int totalAnimSteps, unsigned int frameWidth,
		unsigned int frameHeight, const sf::String& name = "DEFAULT");
	~Player();

	void setName(const sf::String& name);
	const sf::String& getName() const;

private:

	sf::String m_Name;

};

#endif
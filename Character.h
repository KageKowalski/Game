// Klayton Kowalski

#ifndef CHARACTER_H
#define CHARACTER_H

#include "Entity.h"
#include "Animation.h"

class Character : public Entity, public Animation {

public:

	Character(const sf::Vector2f position, int initAnimStep, unsigned int totalAnimSteps, unsigned int frameWidth,
		unsigned int frameHeight);
	~Character();

	const sf::Vector2f& getVelocity() const;
	bool isUniversal() const;

protected:

	sf::Vector2f m_Velocity;

	bool m_Universal;

};

#endif
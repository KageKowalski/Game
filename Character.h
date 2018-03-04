// Klayton Kowalski

#ifndef CHARACTER_H
#define CHARACTER_H

#include "Entity.h"
#include "Animation.h"

enum class Frame {
	LOOK_DOWN,
	LOOK_UP,
	LOOK_LEFT,
	LOOK_RIGHT
};

class Character : public Entity, public Animation {

public:

	Character(const sf::Vector2f position, int initAnimStep, unsigned int totalAnimSteps, unsigned int frameWidth,
		unsigned int frameHeight);
	~Character();

	void turn(Frame direction);

	const sf::Vector2f& getVelocity() const;
	bool isUniversal() const;
	int getCharacterID() const;

protected:

	sf::Vector2f m_Velocity;

	bool m_Universal;

	int m_CharacterID;

};

#endif
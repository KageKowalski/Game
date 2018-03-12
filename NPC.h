// Klayton Kowalski

#ifndef NPC_H
#define NPC_H

#include "Character.h"

enum class Behavior {
	LOOK_DOWN,
	LOOK_UP,
	LOOK_LEFT,
	LOOK_RIGHT,
	LOOK_AROUND_CLOCKWISE,
	LOOK_AROUND_COUNTERCLOCKWISE,
	LOOK_AROUND_RANDOMLY,
	WALK_AROUND
};

class NPC : public Character {

public:

	NPC(const sf::Vector2f position, int initAnimStep, unsigned int totalAnimSteps, unsigned int frameWidth,
		unsigned int frameHeight, Behavior behavior, const sf::String& name = "DEFAULT NAME");
	virtual ~NPC();

	Behavior getBehavior() const;

	void update(sf::Time deltaTime);

private:

	void resetTargets();

protected:

	Behavior m_Behavior;

	sf::Time m_ElapsedTimeToTarget;
	sf::Time m_WaitTarget;
	sf::Time m_ActiveTarget;

};

#endif
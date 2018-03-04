// Klayton Kowalski

#ifndef CHARACTER_H
#define CHARACTER_H

#include "Entity.h"
#include "Animation.h"

enum class Direction {
	DOWN,
	UP,
	LEFT,
	RIGHT
};

class Character : public Entity, public Animation {

	enum class Frame {
		LOOK_DOWN,
		LOOK_UP,
		LOOK_LEFT,
		LOOK_RIGHT,
		STEP_DOWN_LEFT_FOOT_FORWARD,
		STEP_DOWN_RIGHT_FOOT_FORWARD,
		STEP_UP_LEFT_FOOT_FORWARD,
		STEP_UP_RIGHT_FOOT_FORWARD,
		STEP_LEFT_LEFT_FOOT_FORWARD,
		STEP_LEFT_RIGHT_FOOT_FOWARD,
		STEP_RIGHT_LEFT_FOOT_FORWARD,
		STEP_RIGHT_RIGHT_FOOT_FOWARD
	};

public:

	Character(const sf::Vector2f position, int initAnimStep, unsigned int totalAnimSteps, unsigned int frameWidth,
		unsigned int frameHeight);
	~Character();

	void turn(Direction direction);
	void walk(sf::Time deltaTime, Direction direction);

	const sf::Vector2f& getVelocity() const;
	bool isUniversal() const;
	int getCharacterID() const;

protected:

	sf::Vector2f m_Velocity;

	bool m_Universal;

	int m_CharacterID;

};

#endif
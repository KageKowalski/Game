// Klayton Kowalski

#ifndef CHARACTER_H
#define CHARACTER_H

#include <cmath>
#include "Entity.h"
#include "Animation.h"

enum class Direction {
	DOWN,
	UP,
	LEFT,
	RIGHT
};

class Character : public Entity, public Animation {

public:

	Character(const sf::Vector2f position, int initAnimStep, unsigned int totalAnimSteps, unsigned int frameWidth,
		unsigned int frameHeight);
	~Character();

	void walk(Direction direction);
	void run(Direction direction);

	void update(sf::Time deltaTime);

	const sf::Vector2f& getVelocity() const;
	bool isUniversal() const;
	bool isMoving() const;
	int getCharacterID() const;

protected:

	sf::Vector2f m_Velocity;

	bool m_Universal;

	int m_CharacterID;

	sf::Time m_ElapsedTime;

	static const unsigned int m_WALK_DOWN_SEQUENCE[4];
	static const unsigned int m_WALK_UP_SEQUENCE[4];
	static const unsigned int m_WALK_LEFT_SEQUENCE[4];
	static const unsigned int m_WALK_RIGHT_SEQUENCE[4];
	static const unsigned int m_RUN_DOWN_SEQUENCE[4];
	static const unsigned int m_RUN_UP_SEQUENCE[4];
	static const unsigned int m_RUN_LEFT_SEQUENCE[4];
	static const unsigned int m_RUN_RIGHT_SEQUENCE[4];

	static const float m_WALK_VELOCITY;
	static const float m_RUN_VELOCITY;

	size_t m_SequenceStep;

	Direction m_DirectionFacing;

	bool m_Moving;

};

#endif

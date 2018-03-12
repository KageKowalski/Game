// Klayton Kowalski

#include "NPC.h"

NPC::NPC(const sf::Vector2f position, int initAnimStep, unsigned int totalAnimSteps, unsigned int frameWidth,
	unsigned int frameHeight, Behavior behavior, const sf::String& name)
	: Character(position, initAnimStep, totalAnimSteps, frameWidth, frameHeight, name)
{
	m_Behavior = behavior;
	resetTargets();
}

NPC::~NPC() {}

Behavior NPC::getBehavior() const {
	return m_Behavior;
}

void NPC::update(sf::Time deltaTime) {
	m_ElapsedTimeToTarget += deltaTime;
	bool transition = false;

	if(isMoving() == false) {
		bool progress = m_ElapsedTimeToTarget >= m_WaitTarget;

		switch (m_Behavior) {
		case Behavior::LOOK_DOWN:
		case Behavior::LOOK_UP:
		case Behavior::LOOK_LEFT:
		case Behavior::LOOK_RIGHT:
			m_ElapsedTimeToTarget = sf::Time::Zero;
			break;

		case Behavior::LOOK_AROUND_CLOCKWISE:
			if (progress) {
				turn(true);
				resetTargets();
			}
			break;
		case Behavior::LOOK_AROUND_COUNTERCLOCKWISE:
			if (progress) {
				turn(false);
				resetTargets();
			}
			break;
		case Behavior::LOOK_AROUND_RANDOMLY:
			if (progress) {
				turn(getRandomDirection());
				resetTargets();
			}
			break;

		case Behavior::WALK_AROUND:
			if (progress) {
				transition = true;
				resetTargets();
			}
			break;
		}
	}

	if (isMoving() || transition) {
		bool progress = m_ElapsedTimeToTarget >= m_ActiveTarget;

		switch (m_Behavior) {
		case Behavior::WALK_AROUND:
			if (!progress) {
				if (transition) walk(getRandomDirection());
				else walk(m_DirectionFacing);
			}
			else resetTargets();
			break;
		}
	}

	Character::update(deltaTime);
}

void NPC::resetTargets() {
	m_ElapsedTimeToTarget = sf::Time::Zero;

	float waitTarget = m_Generator.nextFloat() * 3.0f + 1.0f;
	float activeTarget = m_Generator.nextFloat() * 0.5f + 0.5f;

	m_WaitTarget = sf::seconds(waitTarget);
	m_ActiveTarget = sf::seconds(activeTarget);
}
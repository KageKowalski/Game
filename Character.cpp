// Klayton Kowalski

#include "Character.h"

Character::Character(const sf::Vector2f position, int initAnimStep, unsigned int totalAnimSteps, unsigned int frameWidth,
	unsigned int frameHeight)
	: Entity(position), Animation(initAnimStep, totalAnimSteps, frameWidth, frameHeight)
{}

Character::~Character() {}

const sf::Vector2f& Character::getVelocity() const {
	return m_Velocity;
}

bool Character::isUniversal() const {
	return m_Universal;
}
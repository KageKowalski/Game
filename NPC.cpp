// Klayton Kowalski

#include "NPC.h"

NPC::NPC(const sf::Vector2f position, int initAnimStep, unsigned int totalAnimSteps, unsigned int frameWidth,
	unsigned int frameHeight, Behavior behavior, const sf::String& name)
	: Character(position, initAnimStep, totalAnimSteps, frameWidth, frameHeight, name)
{
	m_Behavior = behavior;
}

NPC::~NPC() {}

Behavior NPC::getBehavior() const {
	return m_Behavior;
}

void NPC::update(sf::Time deltaTime) {


	Character::update(deltaTime);
}
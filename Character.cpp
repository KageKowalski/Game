// Klayton Kowalski

#include "Character.h"

Character::Character(const sf::Vector2f position, int initAnimStep, unsigned int totalAnimSteps, unsigned int frameWidth,
	unsigned int frameHeight)
	: Entity(position), Animation(initAnimStep, totalAnimSteps, frameWidth, frameHeight)
{
	m_Universal = true;
	m_CharacterID = -1;
}

Character::~Character() {}

void Character::turn(Frame direction) {
	switch (direction) {
	case Frame::LOOK_DOWN:
		m_CurrAnimStep = 0;
		break;
	case Frame::LOOK_UP:
		m_CurrAnimStep = 1;
		break;
	case Frame::LOOK_LEFT:
		m_CurrAnimStep = 2;
		break;
	case Frame::LOOK_RIGHT:
		m_CurrAnimStep = 3;
		break;
	}
}

const sf::Vector2f& Character::getVelocity() const {
	return m_Velocity;
}

bool Character::isUniversal() const {
	return m_Universal;
}

int Character::getCharacterID() const {
	return m_CharacterID;
}
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

void Character::turn(Direction direction) {
	switch (direction) {
	case Direction::DOWN:
		m_CurrAnimStep = 0;
		break;
	case Direction::UP:
		m_CurrAnimStep = 1;
		break;
	case Direction::LEFT:
		m_CurrAnimStep = 2;
		break;
	case Direction::RIGHT:
		m_CurrAnimStep = 3;
		break;
	}
}

void Character::walk(sf::Time deltaTime, Direction direction) {
	switch (direction) {
	case Direction::DOWN:
		m_Velocity = sf::Vector2f(0.0f, 25.0f);
		m_Position += m_Velocity * deltaTime.asSeconds();
		break;
	case Direction::UP:
		m_Velocity = sf::Vector2f(0.0f, -25.0f);
		m_Position += m_Velocity * deltaTime.asSeconds();
		break;
	case Direction::LEFT:
		m_Velocity = sf::Vector2f(-25.0f, 0.0f);
		m_Position += m_Velocity * deltaTime.asSeconds();
		break;
	case Direction::RIGHT:
		m_Velocity = sf::Vector2f(25.0f, 0.0f);
		m_Position += m_Velocity * deltaTime.asSeconds();
		break;
	}
	m_Velocity = sf::Vector2f(0.0f, 0.0f);
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
// Klayton Kowalski

#include "Player.h"

Player::Player(const sf::Vector2f position, int initAnimStep, unsigned int totalAnimSteps, unsigned int frameWidth,
	unsigned int frameHeight, const sf::String& name)
	: Character(position, initAnimStep, totalAnimSteps, frameWidth, frameHeight)
{
	m_TextureCoords = sf::Vector2f(0.0f, 0.0f);
	m_Universal = true;
	m_Name = name;
}

Player::~Player() {}

void Player::setName(const sf::String& name) {
	m_Name = name;
}

const sf::String& Player::getName() const {
	return m_Name;
}
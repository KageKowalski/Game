// Klayton Kowalski

#include "Player.h"

Player::Player(const sf::Vector2f position, int initAnimStep, unsigned int totalAnimSteps, unsigned int frameWidth,
	unsigned int frameHeight, const sf::String& name)
	: Character(position, initAnimStep, totalAnimSteps, frameWidth, frameHeight, name)
{
	m_TextureCoords = sf::Vector2f(0.0f, 0.0f);
	m_Universal = true;
	m_CharacterID = 0;
}

Player::~Player() {}
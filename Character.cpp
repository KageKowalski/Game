// Klayton Kowalski

#include "Character.h"

Character::Character(const sf::Vector2f position, int initAnimStep, unsigned int totalAnimSteps, unsigned int frameWidth,
	unsigned int frameHeight)
	: Entity(position), Animation(initAnimStep, totalAnimSteps, frameWidth, frameHeight)
{
	m_CenterPosition = sf::Vector2f(position.x + (static_cast<float>(frameWidth) / 2.0f),
		position.y + (static_cast<float>(frameHeight) / 1.25f));
	m_Universal = true;
	m_CharacterID = -1;
	m_CurrFrame = static_cast<Frame>(initAnimStep);
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
		m_CenterPosition += m_Velocity * deltaTime.asSeconds();
		break;
	case Direction::UP:
		m_Velocity = sf::Vector2f(0.0f, -25.0f);
		m_Position += m_Velocity * deltaTime.asSeconds();
		m_CenterPosition += m_Velocity * deltaTime.asSeconds();
		break;
	case Direction::LEFT:
		m_Velocity = sf::Vector2f(-25.0f, 0.0f);
		m_Position += m_Velocity * deltaTime.asSeconds();
		m_CenterPosition += m_Velocity * deltaTime.asSeconds();
		break;
	case Direction::RIGHT:
		m_Velocity = sf::Vector2f(25.0f, 0.0f);
		m_Position += m_Velocity * deltaTime.asSeconds();
		m_CenterPosition += m_Velocity * deltaTime.asSeconds();
		break;
	}
	m_Velocity = sf::Vector2f(0.0f, 0.0f);
}

void Character::update(sf::Time deltaTime) {
	if (m_Velocity != sf::Vector2f(0.0f, 0.0f)) {
		m_ElapsedTime += deltaTime;
	}
	else {
		switch (mapFrameToDirection(m_CurrFrame)) {
		case Direction::DOWN:
			m_CurrAnimStep = static_cast<unsigned int>(LOOK_DOWN);
			break;
		case Direction::UP:
			m_CurrAnimStep = static_cast<unsigned int>(LOOK_UP);
			break;
		case Direction::LEFT:
			m_CurrAnimStep = static_cast<unsigned int>(LOOK_LEFT);
			break;
		case Direction::RIGHT:
			m_CurrAnimStep = static_cast<unsigned int>(LOOK_RIGHT);
			break;
		}
		m_ElapsedTime = sf::Time::Zero;
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

Direction Character::mapFrameToDirection(Frame frame) {
	switch (frame) {
	case LOOK_DOWN:
	case STEP_DOWN_LEFT_FOOT_FORWARD:
	case STEP_DOWN_RIGHT_FOOT_FORWARD:
		return Direction::DOWN;
	case LOOK_UP:
	case STEP_UP_LEFT_FOOT_FORWARD:
	case STEP_UP_RIGHT_FOOT_FORWARD:
		return Direction::UP;
	case LOOK_LEFT:
	case STEP_LEFT_LEFT_FOOT_FORWARD:
	case STEP_LEFT_RIGHT_FOOT_FOWARD:
		return Direction::LEFT;
	case LOOK_RIGHT:
	case STEP_RIGHT_LEFT_FOOT_FORWARD:
	case STEP_RIGHT_RIGHT_FOOT_FOWARD:
		return Direction::RIGHT;
	}
}
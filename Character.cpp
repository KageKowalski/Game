// Klayton Kowalski

#include "Character.h"

const unsigned int Character::m_WALK_DOWN_SEQUENCE[4]	{ 0, 4, 0, 5 };
const unsigned int Character::m_WALK_UP_SEQUENCE[4]		{ 1, 6, 1, 7 };
const unsigned int Character::m_WALK_LEFT_SEQUENCE[4]	{ 2, 8, 2, 9 };
const unsigned int Character::m_WALK_RIGHT_SEQUENCE[4]	{ 3, 10, 3, 11 };
const unsigned int Character::m_RUN_DOWN_SEQUENCE[4]	{ 12, 16, 12, 17 };
const unsigned int Character::m_RUN_UP_SEQUENCE[4]		{ 13, 18, 13, 19 };
const unsigned int Character::m_RUN_LEFT_SEQUENCE[4]	{ 14, 20, 14, 21 };
const unsigned int Character::m_RUN_RIGHT_SEQUENCE[4]	{ 15, 22, 15, 23 };

const float Character::m_WALK_VELOCITY = 25.0f;
const float Character::m_RUN_VELOCITY = 60.0f;

Character::Character(const sf::Vector2f position, int initAnimStep, unsigned int totalAnimSteps, unsigned int frameWidth,
	unsigned int frameHeight, const sf::String& name)
	: Entity(position), Animation(initAnimStep, totalAnimSteps, frameWidth, frameHeight)
{
	m_CenterPosition = sf::Vector2f(position.x + (static_cast<float>(frameWidth) / 2.0f),
		position.y + static_cast<float>(frameHeight - 8.0f));
	m_Name = name;
	m_Universal = true;
	m_Moving = false;
	m_CharacterID = -1;
	m_SequenceStep = 0;
	m_DirectionFacing = Direction::DOWN;
}

Character::~Character() {}

void Character::walk(Direction direction) {
	m_DirectionFacing = direction;

	switch (m_DirectionFacing) {
	case Direction::DOWN:
		m_Velocity += sf::Vector2f(0.0f, m_WALK_VELOCITY);
		break;
	case Direction::UP:
		m_Velocity += sf::Vector2f(0.0f, -m_WALK_VELOCITY);
		break;
	case Direction::LEFT:
		m_Velocity += sf::Vector2f(-m_WALK_VELOCITY, 0.0f);
		break;
	case Direction::RIGHT:
		m_Velocity += sf::Vector2f(m_WALK_VELOCITY, 0.0f);
		break;
	}
}

void Character::run(Direction direction) {
	m_DirectionFacing = direction;

	switch (m_DirectionFacing) {
	case Direction::DOWN:
		m_Velocity += sf::Vector2f(0.0f, m_RUN_VELOCITY);
		break;
	case Direction::UP:
		m_Velocity += sf::Vector2f(0.0f, -m_RUN_VELOCITY);
		break;
	case Direction::LEFT:
		m_Velocity += sf::Vector2f(-m_RUN_VELOCITY, 0.0f);
		break;
	case Direction::RIGHT:
		m_Velocity += sf::Vector2f(m_RUN_VELOCITY, 0.0f);
		break;
	}
}

void Character::update(sf::Time deltaTime) {
	bool useWalkSequence = true;

	if (m_Velocity == sf::Vector2f(0.0f, 0.0f)) {
		m_Moving = false;
		m_ElapsedTime = sf::Time::Zero;
		m_SequenceStep = 0;
	}
	else {
		m_Moving = true;

		m_Position += m_Velocity * deltaTime.asSeconds();
		m_CenterPosition += m_Velocity * deltaTime.asSeconds();

		if(fabs(m_Velocity.x) == m_RUN_VELOCITY || fabs(m_Velocity.y) == m_RUN_VELOCITY) useWalkSequence = false;

		m_Velocity = sf::Vector2f(0.0f, 0.0f);

		m_ElapsedTime += deltaTime;

		if (m_ElapsedTime >= (useWalkSequence ? sf::seconds(0.25f) : sf::seconds(0.11f))) {
			m_ElapsedTime = sf::Time::Zero;
			m_SequenceStep = (m_SequenceStep + 1) % 4;
		}
	}

	switch (m_DirectionFacing) {
	case Direction::DOWN:
		m_CurrAnimStep = useWalkSequence ? m_WALK_DOWN_SEQUENCE[m_SequenceStep] : m_RUN_DOWN_SEQUENCE[m_SequenceStep];
		break;
	case Direction::UP:
		m_CurrAnimStep = useWalkSequence ? m_WALK_UP_SEQUENCE[m_SequenceStep] : m_RUN_UP_SEQUENCE[m_SequenceStep];
		break;
	case Direction::LEFT:
		m_CurrAnimStep = useWalkSequence ? m_WALK_LEFT_SEQUENCE[m_SequenceStep] : m_RUN_LEFT_SEQUENCE[m_SequenceStep];
		break;
	case Direction::RIGHT:
		m_CurrAnimStep = useWalkSequence ? m_WALK_RIGHT_SEQUENCE[m_SequenceStep] : m_RUN_RIGHT_SEQUENCE[m_SequenceStep];
		break;
	}
}

void Character::setName(const sf::String& name) {
	m_Name = name;
}

const sf::String& Character::getName() const {
	return m_Name;
}

const sf::Vector2f& Character::getVelocity() const {
	return m_Velocity;
}

bool Character::isUniversal() const {
	return m_Universal;
}

bool Character::isMoving() const {
	return m_Moving;
}

int Character::getCharacterID() const {
	return m_CharacterID;
}
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
	m_SequenceStep = 0;
	m_DirectionFacing = Direction::DOWN;

	EventBus::get().registerListener(Event::EventType::EV_TURNDOWN, this);
	EventBus::get().registerListener(Event::EventType::EV_TURNUP, this);
	EventBus::get().registerListener(Event::EventType::EV_TURNLEFT, this);
	EventBus::get().registerListener(Event::EventType::EV_TURNRIGHT, this);
	EventBus::get().registerListener(Event::EventType::EV_WALKDOWN, this);
	EventBus::get().registerListener(Event::EventType::EV_WALKUP, this);
	EventBus::get().registerListener(Event::EventType::EV_WALKLEFT, this);
	EventBus::get().registerListener(Event::EventType::EV_WALKRIGHT, this);
	EventBus::get().registerListener(Event::EventType::EV_RUNDOWN, this);
	EventBus::get().registerListener(Event::EventType::EV_RUNUP, this);
	EventBus::get().registerListener(Event::EventType::EV_RUNLEFT, this);
	EventBus::get().registerListener(Event::EventType::EV_RUNRIGHT, this);
}

Character::~Character() {
	EventBus::get().removeListener(Event::EventType::EV_TURNDOWN, this);
	EventBus::get().removeListener(Event::EventType::EV_TURNUP, this);
	EventBus::get().removeListener(Event::EventType::EV_TURNLEFT, this);
	EventBus::get().removeListener(Event::EventType::EV_TURNRIGHT, this);
	EventBus::get().removeListener(Event::EventType::EV_WALKDOWN, this);
	EventBus::get().removeListener(Event::EventType::EV_WALKUP, this);
	EventBus::get().removeListener(Event::EventType::EV_WALKLEFT, this);
	EventBus::get().removeListener(Event::EventType::EV_WALKRIGHT, this);
	EventBus::get().removeListener(Event::EventType::EV_RUNDOWN, this);
	EventBus::get().removeListener(Event::EventType::EV_RUNUP, this);
	EventBus::get().removeListener(Event::EventType::EV_RUNLEFT, this);
	EventBus::get().removeListener(Event::EventType::EV_RUNRIGHT, this);
}

void Character::turn(Direction direction) {
	m_DirectionFacing = direction;
}

void Character::turn(bool clockwise) {
	switch (m_DirectionFacing) {
	case Direction::DOWN:
		m_DirectionFacing = clockwise ? Direction::LEFT : Direction::RIGHT;
		break;
	case Direction::UP:
		m_DirectionFacing = clockwise ? Direction::RIGHT : Direction::LEFT;
		break;
	case Direction::LEFT:
		m_DirectionFacing = clockwise ? Direction::UP : Direction::DOWN;
		break;
	case Direction::RIGHT:
		m_DirectionFacing = clockwise ? Direction::DOWN : Direction::UP;
		break;
	}
}

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

Direction Character::getDirection() const {
	return m_DirectionFacing;
}

bool Character::isMoving() const {
	return m_Moving;
}

Direction Character::getRandomDirection() const {
	int random = m_Generator.nextInt(0, 3);

	switch (random) {
	case 0:
		return Direction::DOWN;
	case 1:
		return Direction::UP;
	case 2:
		return Direction::LEFT;
	case 3:
		return Direction::RIGHT;
	}
}

bool Character::collision(const Collidable& obj) const {
	sf::FloatRect thisBounds = getGlobalBounds();
	sf::FloatRect otherBounds = obj.getGlobalBounds();

	if (thisBounds.contains(otherBounds.left, otherBounds.top))
		return true;

	return false;
}

sf::FloatRect Character::getGlobalBounds() const {
	sf::FloatRect globalBounds;

	globalBounds.left = getPosition().x;
	globalBounds.top = getPosition().y;

	globalBounds.width = getFrameWidth();
	globalBounds.height = getFrameHeight();

	return globalBounds;
}

void Character::handleEvent(Event* const e) {
	switch (e->getType()) {
	case Event::EventType::EV_TURNDOWN:
		if (dynamic_cast<TurnDownEvent*>(e)->getTargetID() == m_ID)
			turn(Direction::DOWN);
		break;
	case Event::EventType::EV_TURNUP:
		if (dynamic_cast<TurnUpEvent*>(e)->getTargetID() == m_ID)
			turn(Direction::UP);
		break;
	case Event::EventType::EV_TURNLEFT:
		if (dynamic_cast<TurnLeftEvent*>(e)->getTargetID() == m_ID)
			turn(Direction::LEFT);
		break;
	case Event::EventType::EV_TURNRIGHT:
		if (dynamic_cast<TurnRightEvent*>(e)->getTargetID() == m_ID)
			turn(Direction::RIGHT);
		break;
	case Event::EventType::EV_WALKDOWN:
		if (dynamic_cast<WalkDownEvent*>(e)->getTargetID() == m_ID)
			walk(Direction::DOWN);
		break;
	case Event::EventType::EV_WALKUP:
		if (dynamic_cast<WalkUpEvent*>(e)->getTargetID() == m_ID)
			walk(Direction::UP);
		break;
	case Event::EventType::EV_WALKLEFT:
		if (dynamic_cast<WalkLeftEvent*>(e)->getTargetID() == m_ID)
			walk(Direction::LEFT);
		break;
	case Event::EventType::EV_WALKRIGHT:
		if (dynamic_cast<WalkRightEvent*>(e)->getTargetID() == m_ID)
			walk(Direction::RIGHT);
		break;
	case Event::EventType::EV_RUNDOWN:
		if (dynamic_cast<RunDownEvent*>(e)->getTargetID() == m_ID)
			run(Direction::DOWN);
		break;
	case Event::EventType::EV_RUNUP:
		if (dynamic_cast<RunUpEvent*>(e)->getTargetID() == m_ID)
			run(Direction::UP);
		break;
	case Event::EventType::EV_RUNLEFT:
		if (dynamic_cast<RunLeftEvent*>(e)->getTargetID() == m_ID)
			run(Direction::LEFT);
		break;
	case Event::EventType::EV_RUNRIGHT:
		if (dynamic_cast<RunRightEvent*>(e)->getTargetID() == m_ID)
			run(Direction::RIGHT);
		break;
	}
}
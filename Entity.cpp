// Klayton Kowalski

#include "Entity.h"

unsigned int Entity::m_TotalEntities = 0;

Entity::Entity(const sf::Vector2f& position) {
	m_TotalEntities++;

    m_ID = Utility::unique_id();

	m_Position = position;
	m_CenterPosition = position;
	m_TextureCoords = sf::Vector2f(-1.0f, -1.0f);
}

Entity::~Entity() {
	m_TotalEntities--;
}

unsigned int Entity::getTotalEntities() const {
	return m_TotalEntities;
}

const sf::Vector2f& Entity::getPosition() const {
	return m_Position;
}

const sf::Vector2f& Entity::getCenterPosition() const {
	return m_CenterPosition;
}

const sf::Vector2f& Entity::getTextureCoords() const {
	return m_TextureCoords;
}

unsigned int Entity::getID() const {
	return m_ID;
}

void Entity::setPosition(const sf::Vector2f& position) {
	sf::Vector2f centerPosOffset = position - m_Position;

	m_Position = position;
	m_CenterPosition = position + centerPosOffset;
}

void Entity::setCenterPosition(const sf::Vector2f centerPosition) {
	sf::Vector2f positionOffset = centerPosition - m_CenterPosition;

	m_CenterPosition = centerPosition;
	m_Position = centerPosition + positionOffset;
}

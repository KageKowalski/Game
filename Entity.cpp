// Klayton Kowalski

#include "Entity.h"

Entity::Entity(const sf::Vector2f& position) {
	m_TotalEntities++;
	m_Position = position;
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
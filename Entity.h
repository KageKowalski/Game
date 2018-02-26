// Klayton Kowalski

#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

class Entity {

public:

	Entity(const sf::Vector2f& position);
	~Entity();

	unsigned int getTotalEntities() const;
	const sf::Vector2f& getPosition() const;

protected:

	sf::Vector2f m_Position;

private:

	static unsigned int m_TotalEntities;

};

unsigned int Entity::m_TotalEntities = 0;

#endif
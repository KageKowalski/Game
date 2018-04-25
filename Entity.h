// Klayton Kowalski
 
#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include "Chrono.h"
#include "Utility.h"

// An entity is any object that may have an influence on some other object on a tile map.
// For example, darting arrows, characters, and loot drops are all entities.
// This is of course an abstract class. Lots of subclasses follow.
class Entity {

public:

	// Constructor takes a position of the entity on the map.
	Entity(const sf::Vector2f& position);
	~Entity();

	// Retrieves the total amount of entities that are currently being loaded.
	unsigned int getTotalEntities() const;

	// Retrieves the position.
	const sf::Vector2f& getPosition() const;

	// Retrieves the center position.
	const sf::Vector2f& getCenterPosition() const;

	// Retrieves the top-left coordinate of the entity's location in its sprite sheet.
	const sf::Vector2f& getTextureCoords() const;

	// Retrieves this entity's unique ID value.
	unsigned int getID() const;

	// Sets the entity's position.
	// Automatically readjusts center position according to new position.
	void setPosition(const sf::Vector2f& position);

	// Sets the entity's center position.
	// Automatically readjusts position according to new center position.
	void setCenterPosition(const sf::Vector2f centerPosition);

protected:

	// Position in pixel units. Often will be used for converting sprite to verticies.
	sf::Vector2f m_Position;

	// Center position. Often will be used for physics calculations and camera attachment.
	// May not be the exact center position, but rather the center position of the sprite's
	// bottom-center 16x16 pixels. This is where the entity is actually standing or existing.
	sf::Vector2f m_CenterPosition;

	// Top-left coordinate of the entity's location in its sprite sheet.
	// Used to assist in constructing verticies.
	sf::Vector2f m_TextureCoords;

	// Every entity has its own unique ID value, which is set depending on when the entity
	// was created in relation to every other entity. This can be used to fetch a specific entity.
	unsigned int m_ID;

private:

	// Keeps track of how many entities are currently being loaded.
	// Mainly for debug information.
	static unsigned int m_TotalEntities;

};

#endif

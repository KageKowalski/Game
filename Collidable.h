// Klayton Kowalski

#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#include <SFML/Graphics.hpp>

// Collidable interface contains a blueprint for classes to implement.
// All objects that take up physical space in the game world and can be collided
// with should implement this interface. Collidable does not contain an sf::FloatRect
// to keep track of its physical bounds because we do not want to have to update it
// every time the object moves--there's just no point in doing so.
class Collidable {

public:

	virtual ~Collidable() {}

	// Determines if the current object is colliding with some other object.
	// Pass in other object as the argument.
	virtual bool collision(const Collidable& obj) const = 0;

	// Returns an sf::FloatRect specifying the current object's physical bounds on the map.
	// The sf::FloatRect contains the pixel coordinates of the object's position.
	virtual sf::FloatRect getGlobalBounds() const = 0;

};

#endif
// Klayton Kowalski

#ifndef CHARACTER_H
#define CHARACTER_H

#include <cmath>
#include "Entity.h"
#include "Animation.h"
#include "Random.h"
#include "Events.h"

// THIS CLASS ASSUMES THE FOLLOWING ANIMATION STEP VALUES:
// 0 == Look down
// 1 == Look up
// 2 == Look left
// 3 == Look right
// 4 == Walk down left foot forward
// 5 == Walk down right foot forward
// 6 == Walk up left foot forward
// 7 == Walk up right foot forward
// 8 == Walk left left foot forward
// 9 == Walk left right food forward
// 10 == Walk right left foot forward
// 11 == Walk right left food forward
// 12 == Look down (athletic stance)
// 13 == Look up (athletic stance)
// 14 == Look left (athletic stance)
// 15 == Look right (athletic stance)
// 16 == Run down left foot forward
// 17 == Run down right foot forward
// 18 == Run up left foot forward
// 19 == Run up right foot forward
// 20 == Run left left foot forward
// 21 == Run left right food forward
// 22 == Run right left foot forward
// 23 == Run right left food forward

// All possible directions in which a character can be moving.
// Used internally to decide on velocity.
// Used by other classes to tell Character which direction to move.
enum class Direction {
	DOWN,
	UP,
	LEFT,
	RIGHT
};

// All characters share the following functionalities.
// Characters aren't supposed to be instantiated without dynamically pointing to one of its
// subclass. Using this class as a polymorphic base is recommended when batching a bunch
// of different types of characters into the same vector or list of characters, like in SpriteMap.
class Character : public Entity, public Animation, public EventListener {

public:

	// Constructor takes Entity and Animation information.
	Character(const sf::Vector2f position, int initAnimStep, unsigned int totalAnimSteps, unsigned int frameWidth,
		unsigned int frameHeight, const sf::String& name = "DEFAULT NAME");
	virtual ~Character();

	// Changes the direction in which the character is facing.
	void turn(Direction direction);

	// Turns the character clockwise (true) or counterclockwise (false).
	void turn(bool clockwise);

	// Walk in some cardinal direction. May be called more than once per frame for diagonal motion.
	// Only prepares character's velocity; actual position updates happen in update().
	void walk(Direction direction);

	// Run in some cardinal direction. May be called more than once per frame for diagonal motion.
	// Only prepares character's velocity; actual position updates happen in update().
	void run(Direction direction);

	// Updates the character's position, animation, etc every frame.
	// Extract deltaTime using Clock.
	virtual void update(sf::Time deltaTime);

	// Sets the character's name.
	// Probably not a good idea to be changing names throughout the game, but good for game startup.
	void setName(const sf::String& name);

	// Retrieves the character's name.
	const sf::String& getName() const;

	// Retrieves the character's velocity.
	const sf::Vector2f& getVelocity() const;
	
	// Does this character's sprite stem from the universal sprite sheet?
	bool isUniversal() const;

	// Retrieves the direction in which the character is facing.
	Direction getDirection() const;

	// Did the player receive a position update this frame?
	bool isMoving() const;

	// Handles all events that pertain to character actions.
	void handleEvent(Event* const e) override;

protected:

	// Can be used to generate a random direction with no bias.
	// Typically used in passive NPC movement.
	Direction getRandomDirection() const;

protected:

	// Character's name.
	sf::String m_Name;

	// Velocity in the cardinal directions. Used in position updates.
	sf::Vector2f m_Velocity;

	// Determines whether the character's sprite stems from the universal sprite sheet.
	// Will be automatically set depending on which subclass is instantiated.
	bool m_Universal;

	// Time elpased since last animation step update.
	// Used internally to control a character's unique animation sequence.
	sf::Time m_ElapsedTime;

	// Specifies the animation frame to display based on whether we're walking or running,
	// and depending on which direction we're moving.
	static const unsigned int m_WALK_DOWN_SEQUENCE[4];
	static const unsigned int m_WALK_UP_SEQUENCE[4];
	static const unsigned int m_WALK_LEFT_SEQUENCE[4];
	static const unsigned int m_WALK_RIGHT_SEQUENCE[4];
	static const unsigned int m_RUN_DOWN_SEQUENCE[4];
	static const unsigned int m_RUN_UP_SEQUENCE[4];
	static const unsigned int m_RUN_LEFT_SEQUENCE[4];
	static const unsigned int m_RUN_RIGHT_SEQUENCE[4];

	// Specifies the fixed walking and running velocities.
	static const float m_WALK_VELOCITY;
	static const float m_RUN_VELOCITY;

	// Indicates which step of the animation sequence is currently being displayed.
	// Used internally to progress through a character's unique animation sequence.
	size_t m_SequenceStep;

	// Indicates which cardinal direction the character is facing.
	Direction m_DirectionFacing;

	// Indicates whether the character is moving.
	bool m_Moving;

	// Random number generator.
	// Needed for randomization tasks, especially in NPC movement.
	Random m_Generator;

};

#endif

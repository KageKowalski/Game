// Klayton Kowalski

#ifndef AUTOANIMATION_H
#define AUTOANIMATION_H

#include <SFML/System.hpp>
#include "Animation.h"

// An auto animation is an animation that comes with a binding time step.
// This means that the animation step will be updated on a regular interval, allowing
// us to simulate a flower blowing in the wind every quarter-second, for example.
// This class, like Animation, is to be inherited from.
class AutoAnimation : public Animation {

public:

	// Constructor takes the same arguments as Animation, along with an additional time step.
	AutoAnimation(unsigned int initAnimStep, unsigned int totalAnimSteps, unsigned int frameWidth, unsigned int frameHeight,
		sf::Time timeStep);
	~AutoAnimation();

	// Sets the time step.
	void setTimeStep(sf::Time timeStep);

	// Retrieves the time step.
	sf::Time getTimeStep() const;

	// Collects change in time since last frame and adds it to elapsed time.
	// Once elapsed time reaches the time step, the animation step moves forward by one frame.
	void update(sf::Time deltaTime);

	// Resets the animation back to its very first step.
	void reset();

protected:

	// Time step of the animation.
	// Dictates how quickly the animation step should update.
	sf::Time m_TimeStep;

	// Amout of time elapsed since last animation step update.
	sf::Time m_ElapsedTime;

};

#endif
// Klayton Kowalski

#ifndef AUTOANIMATION_H
#define AUTOANIMATION_H

#include <SFML/System.hpp>
#include "Animation.h"

class AutoAnimation : public Animation {

public:

	AutoAnimation(unsigned int initAnimStep, unsigned int frameWidth, unsigned int frameHeight,
		sf::Time timeStep);
	~AutoAnimation();

	void setTimeStep(sf::Time timeStep);

protected:

	sf::Time m_TimeStep;
	sf::Time m_ElapsedTime;

};

#endif
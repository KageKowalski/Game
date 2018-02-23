// Klayton Kowalski

#include "AutoAnimation.h"

AutoAnimation::AutoAnimation(unsigned int initAnimStep, unsigned int frameWidth, unsigned int frameHeight,
	sf::Time timeStep)
	: Animation(initAnimStep, frameWidth, frameHeight)
{
	m_TimeStep = timeStep;
}

AutoAnimation::~AutoAnimation() {}

void AutoAnimation::setTimeStep(sf::Time timeStep) {
	m_TimeStep = timeStep;
}
// Klayton Kowalski

#include "AutoAnimation.h"

AutoAnimation::AutoAnimation(unsigned int initAnimStep, unsigned int totalAnimSteps, unsigned int frameWidth, unsigned int frameHeight,
	sf::Time timeStep)
	: Animation(initAnimStep, totalAnimSteps, frameWidth, frameHeight)
{
	m_TimeStep = timeStep;
}

AutoAnimation::~AutoAnimation() {}

void AutoAnimation::setTimeStep(sf::Time timeStep) {
	m_TimeStep = timeStep;
}

sf::Time AutoAnimation::getTimeStep() const {
	return m_TimeStep;
}
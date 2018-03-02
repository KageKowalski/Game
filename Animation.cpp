// Klayton Kowalski

#include "Animation.h"

Animation::Animation(unsigned int initAnimStep, unsigned int totalAnimSteps, unsigned int frameWidth, unsigned int frameHeight) {
	m_CurrAnimStep = initAnimStep;
	m_TotalAnimSteps = totalAnimSteps;
	m_FrameWidth = frameWidth;
	m_FrameHeight = frameHeight;
}

Animation::~Animation() {}

void Animation::setCurrAnimStep(unsigned int step) {
	m_CurrAnimStep = step % m_TotalAnimSteps;
}

unsigned int Animation::getCurrAnimStep() const {
	return m_CurrAnimStep;
}

unsigned int Animation::getTotalAnimSteps() const {
	return m_TotalAnimSteps;
}

unsigned int Animation::getFrameWidth() const {
	return m_FrameWidth;
}

unsigned int Animation::getFrameHeight() const {
	return m_FrameHeight;
}
// Klayton Kowalski

#include "Animation.h"

Animation::Animation(unsigned int initAnimStep, unsigned int frameWidth, unsigned int frameHeight) {
	m_CurrAnimStep = initAnimStep;
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
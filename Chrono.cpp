#include "Chrono.h"

Chrono::Chrono() {
	m_FramesElapsed = 0;
	m_TimeElapsed = sf::Time::Zero;
	m_LastTime = sf::Time::Zero;
	m_FPS = 0;
}

Chrono::~Chrono() {}

void Chrono::tick() {
	// Gets called once per frame
	m_FramesElapsed++;

	// Add time since last frame
	m_LastTime = m_Clock.restart();
	m_TimeElapsed += m_LastTime;

	// If time elapsed is >= 1.0f second, update FPS
	if (m_TimeElapsed >= sf::seconds(1.0f)) {
		m_FPS = m_FramesElapsed;

		m_FramesElapsed = 0;
		m_TimeElapsed = sf::Time::Zero;
	}
}

unsigned int Chrono::getFPS() const {
	return m_FPS;
}

sf::Time Chrono::getDeltaTime() const {
	return m_LastTime;
}
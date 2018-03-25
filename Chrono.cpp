// Klayton Kowalski

#include "Chrono.h"

Chrono::Chrono() {
	m_FramesElapsed = 0;
	m_FPS = 0;
}

Chrono::~Chrono() {}

void Chrono::tick() {
	m_FramesElapsed++;

	m_LastTime = m_Clock.restart();
	m_TimeElapsed += m_LastTime;

	if (m_TimeElapsed >= sf::seconds(1.0f)) {
		m_FPS = m_FramesElapsed;

		m_FramesElapsed = 0;
		m_TimeElapsed = sf::Time::Zero;
	}
}

unsigned int Chrono::getFPS() const {
	return m_FPS;
}

const sf::Time& Chrono::getDeltaTime() const {
	return m_LastTime;
}

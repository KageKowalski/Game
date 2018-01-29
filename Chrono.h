#ifndef CHRONO_H
#define CHRONO_H

#include <SFML/System.hpp>

class Chrono {

public:

	Chrono();
	~Chrono();

	// Progresses clock forward, updates FPS
	void tick();

	// Accessors
	unsigned int getFPS() const;
	sf::Time getDeltaTime() const;

private:

	// High performance clock that's always internally progressing
	sf::Clock m_Clock;

	// Frames elapsed during the current second
	unsigned int m_FramesElapsed;

	// Time elapsed during the current second
	sf::Time m_TimeElapsed;

	// Time elapsed since last frame
	sf::Time m_LastTime;

	// Frames per second based on most recently completed second
	unsigned int m_FPS;

};

#endif
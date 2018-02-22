// Klayton Kowalski

#ifndef CHRONO_H
#define CHRONO_H

#include <SFML/System.hpp>

// High performance clock. Used to make graphical and physics updates relative to
// the change in time since last frame (frame rate independence).
class Chrono {

public:

	// Constructor takes nothing. As soon as a clock is constructed, it immeditately
	// begins ticking.
	Chrono();
	~Chrono();

	// Progresses the clock forward by the amount of time between the previous frame
	// and the current frame.
	void tick();

	// Retrieves the frame rate.
	unsigned int getFPS() const;

	// Retrieves the change in time since last frame.
	sf::Time getDeltaTime() const;

private:

	// High performance clock that's always internally progressing.
	sf::Clock m_Clock;

	// Frames elapsed during the current second.
	// This may be clamped to a maximum value, depending on if the render window clamped
	// the maximum frame rate.
	unsigned int m_FramesElapsed;

	// Amount of time elapsed since the previous whole second.
	// This value is used to calculate FPS and is reset upon reaching the next whole second.
	sf::Time m_TimeElapsed;

	// Time elapsed since last frame.
	// This value is used to help progress m_TimeElapsed so it can properly reach the next
	// whole second.
	sf::Time m_LastTime;

	// Frames per second (FPS) based on most recently completed second.
	// This may be clamped to a maximum value, depending on if the render window clamped
	// the maximum frame rate.
	unsigned int m_FPS;

};

#endif
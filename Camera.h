// Klayton Kowalski

#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics.hpp>

// Wrapper class for a camera. The render window is actively using its own camera,
// and this camera is separate from that. The relationship between the render window's
// camera and this camera is that whenever we make some sort of update or change to
// this camera, we need to pass it to the render window and update its camera.
class Camera {

public:

	// Constructor takes a rectangle that acts as the size of the viewport in pixels.
	// We want to keep the size of the viewport the same as the size of the video mode,
	// or the size of the render window, so size can be extracted from the current 
	// video mode in Settings.
	Camera(const sf::Vector2f& size);
	~Camera();

	// Resizes the viewport to match a change in the render window's video mode.
	// Whenever the video mode is updated in Settings, extract it and pass it through this
	// function.
	void resize(const sf::Vector2f& size);

	// Dialates or magnifies the viewport, effectively zooming.
	// This function works relative to the current viewport size.
	void zoom(float factor);

	// Updates the camera relative to change in time since last frame.
	// Extract deltaTime from Clock.
	void update(sf::Time deltaTime);
    
    // Sets the velocity of the camera.
    void setVelocity(const sf::Vector2f& velocity);

	// Retrieves the viewport.
	const sf::View& getView() const;

private:

	// The actual camera itself. Dictates the viewport.
	sf::View m_View;
    
    // Camera's velocity. Used when moving the camera independently of the player.
    sf::Vector2f m_Velocity;

};

#endif

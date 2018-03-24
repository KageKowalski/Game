// Klayton Kowalski

#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics.hpp>
#include "Chrono.h"

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
	// Extract deltaTime from Clock.
	void zoom(float factor);

	// Rotates the viewport by the specified angle, measured in degrees.
	// WARNING: A wonky orientation can lead to confusing or unintuitive controls.
	// This function works relative to the current viewport orientation.
	// Extract deltaTime from Clock.
	void rotate(float angle);

	// Pans the camera in the cardinal directions.
	// Extract deltaTime from Clock.
	void pan(const sf::Vector2f& velocity);

	// Instantly resets the viewport orientation to zero degrees.
	void resetOrientation();

	// Makes updates to camera that aren't explicity demanded by the player.
	void update();

	// Sets the camera's position to some location.
	// Typically used for locking the camera to an object.
	void setPosition(const sf::Vector2f& position);

	// Sets the camera's target.
	// Essentially attaches the camera to some object.
	// The target's transform's scale component must be passed in.
	// This is because if a target is scaled by 'x', when it moves 'p' pixels, it actually
	// moves 'x * p' pixels, due to the custom scale.
	void setTarget(const sf::Vector2f& targetPosition, const sf::Vector2f& targetScale = sf::Vector2f(1.0f, 1.0f));

	// Detaches the camera from the target object.
	void detach();

	// Calculates and retrieves the position bounds of the viewport, in pixel units.
	// The position bounds are useful for determining whether a particular vertex
	// is visible on the screen or lies outside of the camera's view.
	const sf::FloatRect& getBounds() const;

	// Retrieves the viewport.
	const sf::View& getView() const;

private:

	// The actual camera itself. Dictates the viewport.
	sf::View m_View;
    
    sf::FloatRect m_Bounds;

	// Position of object that the camera is currently attached to.
	// Nullptr if camera is not attached to any object.
	const sf::Vector2f* m_TargetPosition;

	// Scale of object that the camera is currently attached to.
	// Nullptr if camera is not attached to any object.
	const sf::Vector2f* m_TargetScale;

};

#endif

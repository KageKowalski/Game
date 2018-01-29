#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics.hpp>

class Camera {

public:

	Camera(const sf::Vector2f& size);
	~Camera();

	// Resizes the viewable area
	void resize(const sf::Vector2f& size);

	// Accessors
	const sf::View& getView() const;

private:

	// Camera lens
	sf::View m_View;

};

#endif
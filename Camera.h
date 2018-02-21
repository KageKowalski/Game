#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics.hpp>

class Camera {

public:

	Camera(const sf::Vector2f& size);
	~Camera();

	// Resizes the viewable area
	void resize(const sf::Vector2f& size);
    
    // Mutators
    void setVelocity(const sf::Vector2f& velocity);
    void zoom(float factor);

	// Accessors
	const sf::View& getView() const;
    
    // Updates the Camera
    void update(sf::Time deltaTime);
    

private:

	// Camera lens
	sf::View m_View;
    
    // Velocity
    sf::Vector2f m_Velocity;

};

#endif

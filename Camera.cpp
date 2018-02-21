#include "Camera.h"

Camera::Camera(const sf::Vector2f& size) {
	resize(size);
	m_View.setCenter(sf::Vector2f(size.x / 2.0f, size.y / 2.0f));
}

Camera::~Camera() {}

void Camera::resize(const sf::Vector2f& size) {
	m_View.setSize(size);
}

void Camera::setVelocity(const sf::Vector2f& velocity) {
    m_Velocity = velocity;
}

void Camera::zoom(float factor)
{
    m_View.zoom(factor);
}

const sf::View& Camera::getView() const {
	return m_View;
}

void Camera::update(sf::Time deltaTime)
{
    sf::Vector2f offset;
    offset.x = m_Velocity.x * deltaTime.asSeconds();
    offset.y = m_Velocity.y * deltaTime.asSeconds();
    m_View.move(offset);
}



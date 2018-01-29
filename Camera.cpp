#include "Camera.h"

Camera::Camera(const sf::Vector2f& size) {
	resize(size);
	m_View.setCenter(sf::Vector2f(size.x / 2.0f, size.y / 2.0f));
}

Camera::~Camera() {}

void Camera::resize(const sf::Vector2f& size) {
	m_View.setSize(size);
}

const sf::View& Camera::getView() const {
	return m_View;
}
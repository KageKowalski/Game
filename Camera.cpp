// Klayton Kowalski

#include "Camera.h"

Camera::Camera(const sf::Vector2f& size) {
	resize(size);
	m_View.setCenter(sf::Vector2f(size.x / 2.0f, size.y / 2.0f));
	m_TargetPosition = nullptr;
}

Camera::~Camera() {}

void Camera::resize(const sf::Vector2f& size) {
	m_View.setSize(size);
}

void Camera::zoom(float factor, sf::Time deltaTime) {
	if (factor < 0) m_View.zoom(1.0f - (-factor * deltaTime.asSeconds()));
	else m_View.zoom(1.0f + factor * deltaTime.asSeconds());
}

void Camera::rotate(float angle, sf::Time deltaTime) {
	m_View.rotate(angle * deltaTime.asSeconds());
}

void Camera::pan(const sf::Vector2f& velocity, sf::Time deltaTime) {
	m_View.move(velocity * deltaTime.asSeconds());
}

void Camera::resetOrientation() {
	m_View.setRotation(0.0f);
}

void Camera::update() {
	if (m_TargetPosition == nullptr) return;
	setPosition(sf::Vector2f(m_TargetPosition->x * m_TargetScale->x, m_TargetPosition->y * m_TargetScale->y));
}

void Camera::setPosition(const sf::Vector2f& position) {
	m_View.move(position - m_View.getCenter());
}

void Camera::setTarget(const sf::Vector2f& targetPosition, const sf::Vector2f& targetScale) {
	m_TargetPosition = &targetPosition;
	m_TargetScale = &targetScale;
}

void Camera::detach() {
	m_TargetPosition = nullptr;
	m_TargetScale = nullptr;
}

sf::FloatRect Camera::getBounds() const {
	return sf::FloatRect(m_View.getCenter(), m_View.getSize());
}

const sf::View& Camera::getView() const {
	return m_View;
}

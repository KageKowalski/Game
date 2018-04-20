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

void Camera::zoom(float factor) {
	if (factor < 0) m_View.zoom(1.0f - (-factor * Chrono::get().getDeltaTime().asSeconds()));
	else m_View.zoom(1.0f + factor * Chrono::get().getDeltaTime().asSeconds());
}

void Camera::rotate(float angle) {
	m_View.rotate(angle * Chrono::get().getDeltaTime().asSeconds());
}

void Camera::pan(const sf::Vector2f& velocity) {
	m_View.move(velocity * Chrono::get().getDeltaTime().asSeconds());
}

void Camera::resetOrientation() {
	m_View.setRotation(0.0f);
}

void Camera::update() {
	if (m_TargetPosition == nullptr) return;

	setPosition(sf::Vector2f((m_TargetPosition->x * m_TargetScale->x), (m_TargetPosition->y * m_TargetScale->y)));

    m_Bounds = sf::FloatRect(m_View.getCenter(), m_View.getSize());
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

const sf::FloatRect& Camera::getBounds() const {
    return m_Bounds;
}

const sf::View& Camera::getView() const {
	return m_View;
}

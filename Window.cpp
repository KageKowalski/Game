// Klayton Kowalski

#include "Window.h"

Window::Window(const sf::VideoMode& initMode, const sf::View& view, bool fullscreen) {
	construct(initMode, view, fullscreen);
}

Window::~Window() {}

void Window::resize(const sf::View& view) {
	m_RenderWindow.setView(view);
}

void Window::toggleFullscreen(const sf::VideoMode& initMode, const sf::View& view, bool fullscreen) {
	construct(initMode, view, fullscreen);
}

void Window::construct(const sf::VideoMode& initMode, const sf::View& view, bool fullscreen) {
	if (fullscreen) m_RenderWindow.create(initMode, "Default Title", sf::Style::Fullscreen);
	else m_RenderWindow.create(initMode, "Default Title", sf::Style::Default);

    m_RenderWindow.setVerticalSyncEnabled(true);
	//m_RenderWindow.setFramerateLimit();

	resize(view);
}

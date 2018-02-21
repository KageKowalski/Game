#include "Window.h"

Window::Window(const sf::VideoMode& initMode, const sf::View& view, bool fullscreen) {
	construct(initMode, view, fullscreen);
}

Window::~Window() {}

void Window::resize(const sf::View& view) {
	m_RenderWindow.setView(view);
}

void Window::toggleFullscreen(const Settings* settings, const sf::View view) {
	construct(settings->getCurrVideoMode(), view, settings->isFullscreen());
}

void Window::construct(const sf::VideoMode& initMode, const sf::View& view, bool fullscreen) {
	// Construct in fullscreen mode
	if (fullscreen) m_RenderWindow.create(initMode, "Default Title", sf::Style::Fullscreen);
	// Construct in windowed mode
	else m_RenderWindow.create(initMode, "Default Title", sf::Style::Default);

    m_RenderWindow.setVerticalSyncEnabled(true);
	m_RenderWindow.setFramerateLimit(62);

	resize(view);
}

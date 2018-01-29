#include "Application.h"

Application::Application() {
	m_Window = nullptr;
	m_Settings = nullptr;
	m_Camera = nullptr;
	m_Console = nullptr;
}

Application::~Application() {
	delete m_Window;
	delete m_Settings;
	delete m_Camera;
	delete m_Console;
}

int Application::run() {
	// Check if application initialized properly
	if (!init()) return EXIT_FAILURE;

	// Stores event triggers
	sf::Event e;

	// Game loop
	while (m_Window->m_RenderWindow.isOpen()) {
		// Progress clock forward once per frame
		m_Clock.tick();

		// Process any events that have occurred
		while (m_Window->m_RenderWindow.pollEvent(e)) {
			switch (e.type) {
			case sf::Event::EventType::Closed:
				m_Window->m_RenderWindow.close();
				break;
			case sf::Event::EventType::Resized:
				m_Camera->resize(sf::Vector2f(static_cast<float>(e.size.width), static_cast<float>(e.size.height)));
				m_Window->resize(m_Camera->getView());
				break;
			}
		}

		// Process input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F11)) toggleFullscreen();

		// Present graphics
		m_Window->m_RenderWindow.clear(sf::Color::Black);
		m_Window->m_RenderWindow.draw(*m_Console);
		m_Window->m_RenderWindow.display();
	}

	return EXIT_SUCCESS;
}

bool Application::init() {
	m_Settings = new Settings();

	// Cache startup video mode
	sf::VideoMode initMode = m_Settings->getCurrVideoMode();

	m_Camera = new Camera(sf::Vector2f(static_cast<float>(initMode.width), static_cast<float>(initMode.height)));

	m_Window = new Window(initMode, m_Camera->getView(), m_Settings->isFullscreen());

	m_Console = new Console();

	return true;
}

void Application::toggleFullscreen() {
	m_Settings->toggleFullscreen();

	// Cache current video mode
	sf::VideoMode mode = m_Settings->getCurrVideoMode();

	m_Camera->resize(sf::Vector2f(static_cast<float>(mode.width), static_cast<float>(mode.height)));

	m_Window->toggleFullscreen(m_Settings, m_Camera->getView());
}
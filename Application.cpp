#include "Application.h"


Application::Application() {
	m_Window = nullptr;
	m_Settings = nullptr;
	m_Camera = nullptr;
}

Application::~Application() {
	delete m_Window;
	delete m_Settings;
	delete m_Camera;
}

int Application::run() {
	// Check if application initialized properly
	if (!init()) return EXIT_FAILURE;

	// Stores event triggers
	sf::Event e;
    TileMapBank maps;
    maps.init();
	// Game loop
	while (m_Window->m_RenderWindow.isOpen()) {
		// Progress clock forward once per frame
		m_Clock.tick();

		m_Window->m_RenderWindow.setTitle(sf::String(std::to_string(m_Clock.getFPS())));

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
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) m_Camera->setVelocity(sf::Vector2f(-300, 0));
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) m_Camera->setVelocity(sf::Vector2f( 0, 300));
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) m_Camera->setVelocity(sf::Vector2f( 300, 0));
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) m_Camera->setVelocity(sf::Vector2f( 0,-300));
        if(!(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)||sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)||sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)||sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)))
            m_Camera->setVelocity(sf::Vector2f( 0,0));
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::O)) m_Camera->zoom(1.01f);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::I)) m_Camera->zoom(.99f);
        
        //Update Camera
        m_Camera->update(m_Clock.getDeltaTime());
        m_Window->m_RenderWindow.setView(m_Camera->getView());

		// Present graphics
		m_Window->m_RenderWindow.clear(sf::Color::Black);
        m_Window->m_RenderWindow.draw(maps.getMap());
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

	return true;
}

void Application::toggleFullscreen() {
	m_Settings->toggleFullscreen();

	// Cache current video mode
	sf::VideoMode mode = m_Settings->getCurrVideoMode();

	m_Camera->resize(sf::Vector2f(static_cast<float>(mode.width), static_cast<float>(mode.height)));

	m_Window->toggleFullscreen(m_Settings, m_Camera->getView());
}

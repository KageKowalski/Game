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

	TextSequence ts(sf::seconds(2));
	sf::Font font;
	if(!font.loadFromFile("sansation.ttf")) return EXIT_FAILURE;
	sf::Text t1(L"1. This is a line of text that is being drawn onto the screen.", font);
	t1.setFillColor(sf::Color::Red);
	sf::Text t2(L"2. This is a line of text that is being drawn onto the screen.", font, 64);
	t2.setFillColor(sf::Color::Red);
	sf::Text t3(L"3. This is a line of text that is being drawn onto the screen.", font, 64);
	t3.setFillColor(sf::Color::Red);
	sf::Text t4(L"4. This is a line of text that is being drawn onto the screen.", font, 64);
	t4.setFillColor(sf::Color::Red);
	sf::Text t5(L"5. This is a line of text that is being drawn onto the screen.", font, 64);
	t5.setFillColor(sf::Color::Red);
	ts.appendInstance(t1, sf::seconds(0.1f));
	ts.appendInstance(t2, sf::seconds(0.1f));
	ts.appendInstance(t3, sf::seconds(0.1f));
	ts.appendInstance(t4, sf::seconds(0.1f));
	ts.appendInstance(t5, sf::seconds(0.1f));

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

		ts.update(m_Clock.getDeltaTime());

		// Present graphics
		m_Window->m_RenderWindow.clear(sf::Color::Black);
		ts.draw(m_Window->m_RenderWindow);
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
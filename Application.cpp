#include "Application.h"

Application::Application() : m_Maps(sf::Vector2f(7.0f, 7.0f)) {
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
    
    Music background("Game_Test.wav");
	m_Camera->setTarget(m_Maps.getCurrMap().second->getPlayer()->getCenterPosition(), m_Maps.getScale());

	// Game loop
	while (m_Window->m_RenderWindow.isOpen()) {
		// Progress clock forward once per frame
		m_Clock.tick();

		// Cache change in time since last frame
		sf::Time deltaTime = m_Clock.getDeltaTime();

		m_Window->m_RenderWindow.setTitle(sf::String(std::to_string(m_Clock.getFPS())));

		// Process any events that have occurred
		while (m_Window->m_RenderWindow.pollEvent(e)) {
			switch (e.type) {
			case sf::Event::EventType::Closed:
				m_Window->m_RenderWindow.close();
				break;
			case sf::Event::EventType::Resized:
				sf::VideoMode updatedVideoMode(e.size.width, e.size.height);
				m_Settings->setCurrentVideoMode(updatedVideoMode);
				m_Camera->resize(sf::Vector2f(static_cast<float>(e.size.width), static_cast<float>(e.size.height)));
				m_Window->resize(m_Camera->getView());
				break;
			}
		}
		// Process input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F11)) toggleFullscreen();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) m_Camera->pan(sf::Vector2f(-500.0f, 0.0f), deltaTime);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) m_Camera->pan(sf::Vector2f(0.0f, 500.0f), deltaTime);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) m_Camera->pan(sf::Vector2f(500.0f, 0.0f), deltaTime);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) m_Camera->pan(sf::Vector2f(0.0f, -500.0f), deltaTime);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::O)) m_Camera->zoom(3.0f, deltaTime);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::I)) m_Camera->zoom(-3.0f, deltaTime);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::T)) m_Camera->rotate(120.0f, deltaTime);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::U)) m_Camera->rotate(-120.0f, deltaTime);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Y)) m_Camera->resetOrientation();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) m_Maps.getCurrMap().second->getPlayer()->run(Direction::DOWN);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) m_Maps.getCurrMap().second->getPlayer()->walk(Direction::DOWN);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) m_Maps.getCurrMap().second->getPlayer()->run(Direction::UP);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) m_Maps.getCurrMap().second->getPlayer()->walk(Direction::UP);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) m_Maps.getCurrMap().second->getPlayer()->run(Direction::LEFT);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) m_Maps.getCurrMap().second->getPlayer()->walk(Direction::LEFT);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) m_Maps.getCurrMap().second->getPlayer()->run(Direction::RIGHT);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) m_Maps.getCurrMap().second->getPlayer()->walk(Direction::RIGHT);

		// Update components
		update();

		m_Window->m_RenderWindow.setView(m_Camera->getView());

		m_Maps.update(deltaTime, m_Maps.getCurrMap().second->getPlayer()->getCenterPosition());
        
        //background.startMusic();
		m_Renderer.updateTransform(m_Maps.getTransform(), 1);
		std::vector<sf::Texture> textures = m_Maps.getTextures();
		m_Renderer.updateTexture(textures.at(0), 1);
		m_Renderer.updateTexture(textures.at(1), 4);
		m_Renderer.updateTexture(textures.at(2), 5);
		std::vector<sf::VertexArray> verticies = m_Maps.getVerticies();
		m_Renderer.updateVerticies(verticies.at(0), 1);
		m_Renderer.updateVerticies(verticies.at(1), 2);
		m_Renderer.updateVerticies(verticies.at(2), 3);
		m_Renderer.updateVerticies(verticies.at(3), 4);
		m_Renderer.updateVerticies(verticies.at(4), 5);
		m_Renderer.updateVerticies(verticies.at(5), 6);
        background.setVolume(100.0f);
        m_Settings->setEffectsVolume(100.0f);

		// Draw graphics
		draw();
	}

	return EXIT_SUCCESS;
}

bool Application::init() {
	m_Settings = new Settings();
    m_Settings->setMusicVolume(50.0f);
    m_Settings->setEffectsVolume(50.0f);

	// Cache startup video mode
	sf::VideoMode initMode = m_Settings->getCurrVideoMode();

	m_Camera = new Camera(sf::Vector2f(static_cast<float>(initMode.width), static_cast<float>(initMode.height)));

	m_Window = new Window(initMode, m_Camera->getView(), m_Settings->isFullscreen());

	if (!m_Maps.loadMap(0, m_Settings->getEffectsVolume())) return false;

	return true;
}

void Application::update() {
	m_Camera->update();
}

void Application::draw() {
	m_Window->m_RenderWindow.clear(sf::Color(255, 0, 255));
	m_Window->m_RenderWindow.draw(m_Renderer);
	m_Window->m_RenderWindow.display();
}

void Application::toggleFullscreen() {
	m_Settings->toggleFullscreen();

	// Cache current video mode
	sf::VideoMode mode = m_Settings->getCurrVideoMode();

	m_Camera->resize(sf::Vector2f(static_cast<float>(mode.width), static_cast<float>(mode.height)));

	m_Window->toggleFullscreen(m_Settings->getCurrVideoMode(),m_Camera->getView(),m_Settings->isFullscreen());
}

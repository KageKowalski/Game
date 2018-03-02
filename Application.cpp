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
    
    Music background("Game_Test.wav");
	SpriteMap spritemap(sf::Vector2f(5.0f, 5.0f));
	Character* larvitar = new Player(sf::Vector2f(0.0f, 0.0f), 0, 1, 32, 32, "Larvitar the Bodybuilder");
	std::vector<Character*> characters;
	characters.push_back(larvitar);
	spritemap.build("lar.png", "lar.png", characters);

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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) m_Camera->pan(sf::Vector2f(-500.0f, 0.0f), deltaTime);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) m_Camera->pan(sf::Vector2f(0.0f, 500.0f), deltaTime);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) m_Camera->pan(sf::Vector2f(500.0f, 0.0f), deltaTime);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) m_Camera->pan(sf::Vector2f(0.0f, -500.0f), deltaTime);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::O)) m_Camera->zoom(3.0f, deltaTime);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::I)) m_Camera->zoom(-3.0f, deltaTime);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::T)) m_Camera->rotate(120.0f, deltaTime);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::U)) m_Camera->rotate(-120.0f, deltaTime);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Y)) m_Camera->resetOrientation();

		m_Window->m_RenderWindow.setView(m_Camera->getView());

		// Update components
		update();
        
        background.startMusic();
        background.setMusic(m_TileMapBank.getMap().getMusic());
        
        m_Renderer.updateTexture(m_TileMapBank.getMap().getTileSet(), 1);
        m_Renderer.updateVerticies(m_TileMapBank.getMap().getGroundVertices(), 1);
        m_Renderer.updateVerticies(m_TileMapBank.getMap().getLayerOneVertices(), 2);
        m_Renderer.updateVerticies(m_TileMapBank.getMap().getLayerTwoVertices(), 3);
		m_Renderer.updateTexture(spritemap.getUniversalSpriteSheet(), 4);
		m_Renderer.updateTexture(spritemap.getLocalSpriteSheet(), 5);
		m_Renderer.updateVerticies(spritemap.getUniversalSpriteVerticies(), 4);
		m_Renderer.updateVerticies(spritemap.getLocalSpriteVerticies(), 5);


		// Draw graphics
		draw();
	}

	return EXIT_SUCCESS;
}

bool Application::init() {
	m_Settings = new Settings();

	// Cache startup video mode
	sf::VideoMode initMode = m_Settings->getCurrVideoMode();

	m_Camera = new Camera(sf::Vector2f(static_cast<float>(initMode.width), static_cast<float>(initMode.height)));

	m_Window = new Window(initMode, m_Camera->getView(), m_Settings->isFullscreen());

	if (!m_TileMapBank.init()) return false;

	return true;
}

void Application::update() {
	m_TileMapBank.getMap().updateMap(m_Clock.getDeltaTime());
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

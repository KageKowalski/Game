#include "Application.h"

Application::Application()  {
	m_Window = nullptr;
	m_Settings = nullptr;
	m_Camera = nullptr;
	m_State = GameState::FREEROAM;
	EventBus::get().registerListener(Event::EventType::EV_FULLSCREEN, this);
}

Application::~Application() {
	delete m_Window;
	delete m_Settings;
	delete m_Camera;
}

int Application::run() {
	if (!init()) return EXIT_FAILURE;

	sf::Event e;

	Music background("Game_Test.wav");
    m_Camera->setTarget(MapBank::get().getCurrMap().second->getPlayer()->getCenterPosition(), MapBank::get().getScale());

	while (m_Window->m_RenderWindow.isOpen()) {
		Chrono::get().tick();
		EventBus::get().update();

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

		m_Input.analyze(m_State);

		update();
		std::vector<Character*> reachables = MapBank::get().getCurrMap().second->getReachableCharacters();
		bool touching = MapBank::get().getCurrMap().second->isTouching(MapBank::get().getCurrMap().second->getPlayer(),
			MapBank::get().getCurrMap().second->getPlayer()->getDirection());
		if (reachables.size() > 0)
			m_Window->m_RenderWindow.setTitle(sf::String(std::to_string(Chrono::get().getFPS())) + " | " + reachables.at(reachables.size() - 1)->getName() + " | Touching (1) Yes (0) No: " + std::to_string(touching));
		else m_Window->m_RenderWindow.setTitle(sf::String(std::to_string(Chrono::get().getFPS())) + " | " + MapBank::get().getCurrMap().first->getName() + " | Touching (1) Yes (0) No: " + std::to_string(touching));

		m_Window->m_RenderWindow.setView(m_Camera->getView());

		MapBank::get().update(Chrono::get().getDeltaTime(), MapBank::get().getCurrMap().second->getPlayer()->getCenterPosition(), m_Camera->getBounds());
		Sun::get().update();
		background.startMusic();
		background.setVolume(m_Settings->getMusicVolume());

		m_Renderer.updateTransform(MapBank::get().getTransform(), 1);
		std::vector<sf::Texture> textures = MapBank::get().getTextures();
		m_Renderer.updateTexture(textures.at(0), 1);
		m_Renderer.updateTexture(textures.at(1), 4);
		m_Renderer.updateTexture(textures.at(2), 5);
		std::vector<sf::VertexArray> verticies = MapBank::get().getVerticies();
		m_Renderer.updateVerticies(verticies.at(0), 1);
		m_Renderer.updateVerticies(verticies.at(1), 2);
		m_Renderer.updateVerticies(verticies.at(2), 3);
		m_Renderer.updateVerticies(verticies.at(3), 4);
		m_Renderer.updateVerticies(verticies.at(4), 5);
		m_Renderer.updateVerticies(verticies.at(5), 6);
		m_Renderer.updateVerticies(verticies.at(6), 7);
		m_Window->m_RenderWindow.clear(sf::Color(255, 0, 255));
		m_Window->m_RenderWindow.draw(m_Renderer);
		m_Window->m_RenderWindow.display();
	}

	return EXIT_SUCCESS;
}

bool Application::init() {
    m_Settings = &Settings::get();

	MapBank::get().soundInit(m_Settings->getEffectsVolume());

	sf::VideoMode initMode = m_Settings->getCurrVideoMode();
	m_Camera = new Camera(sf::Vector2f(static_cast<float>(initMode.width), static_cast<float>(initMode.height)));
	m_Window = new Window(initMode, m_Camera->getView(), m_Settings->isFullscreen());

	if (!MapBank::get().loadMap(0)) return false;

	return true;
}

void Application::update() {
    std::unique_ptr<Event> eventPtr = std::make_unique<RadialSoundEvent>();
    EventBus::get().postEvent(eventPtr);
	m_Camera->update();
}

void Application::draw() {
	m_Window->m_RenderWindow.clear(sf::Color(255, 0, 255));
	m_Window->m_RenderWindow.draw(m_Renderer);
	m_Window->m_RenderWindow.display();
}

void Application::toggleFullscreen() {
	m_Settings->toggleFullscreen();

	sf::VideoMode mode = m_Settings->getCurrVideoMode();
	m_Camera->resize(sf::Vector2f(static_cast<float>(mode.width), static_cast<float>(mode.height)));
	m_Window->toggleFullscreen(m_Settings->getCurrVideoMode(), m_Camera->getView(), m_Settings->isFullscreen());
}

void Application::handleEvent(Event* const e) {
	switch (e->getType()) {
	case Event::EventType::EV_FULLSCREEN:
		toggleFullscreen();
		break;
	}
}

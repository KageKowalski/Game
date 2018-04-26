#include "Application.h"

Application::Application()  {
	m_Window = nullptr;
	m_Camera = nullptr;

	m_State = GameState::FREEROAM;

	EventBus::get().registerListener(Event::EventType::EV_FULLSCREEN, this);
	EventBus::get().registerListener(Event::EventType::EV_FULLLOADING, this);
}

Application::~Application() {
	EventBus::get().removeListener(Event::EventType::EV_FULLSCREEN, this);
	EventBus::get().removeListener(Event::EventType::EV_FULLLOADING, this);

	delete m_Window;
	delete m_Camera;
}

int Application::run() {
	if (!init()) return EXIT_FAILURE;

	sf::Event e;

	Music background("Game_Test.wav");
    m_Camera->setTarget(Player::get().getCenterPosition(), MapBank::get().getScale());

	Log::get().print("This is a test of the Log system.");
	Log::get().print("This is a test of the Log system, but without a time stamp.", false);

	while (m_Window->m_RenderWindow.isOpen()) {
		Chrono::get().tick();
		EventBus::get().update();

		m_Window->m_RenderWindow.setTitle(sf::String(std::to_string(Chrono::get().getFPS())));

		while (m_Window->m_RenderWindow.pollEvent(e)) {
			switch (e.type) {
			case sf::Event::EventType::Closed:
				m_Window->m_RenderWindow.close();
				break;
			case sf::Event::EventType::Resized:
				sf::VideoMode updatedVideoMode(e.size.width, e.size.height);
				Settings::get().setCurrentVideoMode(updatedVideoMode);
				m_Camera->resize(sf::Vector2f(static_cast<float>(e.size.width), static_cast<float>(e.size.height)));
				m_Window->resize(m_Camera->getView());
				break;
			}
		}

		m_Input.analyze(m_State);

		update();

		m_Window->m_RenderWindow.setView(m_Camera->getView());

		background.startMusic();
		background.setVolume(Settings::get().getMusicVolume());

		m_Renderer.updateTransform(MapDirector::get().getCurrTransform(), 1);
		std::vector<sf::Texture> textures = MapDirector::get().getCurrTextures();
		m_Renderer.updateTexture(textures.at(0), 1);
		m_Renderer.updateTexture(textures.at(1), 4);
		m_Renderer.updateTexture(textures.at(2), 5);
		std::vector<sf::VertexArray> verticies = MapDirector::get().getCurrVerticies();
		m_Renderer.updateVerticies(verticies.at(0), 1);
		m_Renderer.updateVerticies(verticies.at(1), 2);
		m_Renderer.updateVerticies(verticies.at(2), 3);
		m_Renderer.updateVerticies(verticies.at(3), 4);
		m_Renderer.updateVerticies(verticies.at(4), 5);
		m_Renderer.updateVerticies(verticies.at(5), 6);
		m_Renderer.updateVerticies(verticies.at(6), 7);

		draw();
	}

	return EXIT_SUCCESS;
}

bool Application::init() {
	if (!TextBank::get().init())
		return false;

	sf::VideoMode initMode = Settings::get().getCurrVideoMode();
	m_Camera = new Camera(sf::Vector2f(static_cast<float>(initMode.width), static_cast<float>(initMode.height)));
	m_Window = new Window(initMode, m_Camera->getView(), Settings::get().isFullscreen());

	TileSoundHandler::get().setVolume(Settings::get().getEffectsVolume());

	MapBank::get().init();
	if (!MapDirector::get().loadMap(0)) return false;

	return true;
}

void Application::update() {
    std::unique_ptr<Event> eventPtr = std::make_unique<RadialSoundEvent>();
    EventBus::get().postEvent(eventPtr);
	m_Camera->update();

	MapDirector::get().update();
	Sun::get().update();
}

void Application::draw() {
	m_Window->m_RenderWindow.clear(sf::Color(255, 0, 255));
	m_Window->m_RenderWindow.draw(m_Renderer);
	sf::Text test = TextBank::get().getText(0);
	m_Window->m_RenderWindow.draw(test);
	m_Window->m_RenderWindow.display();
}

void Application::toggleFullscreen() {
	Settings::get().toggleFullscreen();

	sf::VideoMode mode = Settings::get().getCurrVideoMode();
	m_Camera->resize(sf::Vector2f(static_cast<float>(mode.width), static_cast<float>(mode.height)));
	m_Window->toggleFullscreen(Settings::get().getCurrVideoMode(), m_Camera->getView(), Settings::get().isFullscreen());
}

void Application::handleEvent(Event* const e) {
	switch (e->getType()) {
	case Event::EventType::EV_FULLSCREEN:
		toggleFullscreen();
		break;
	case Event::EventType::EV_FULLLOADING:
		m_State = GameState::LOADING;
		break;
	}
}

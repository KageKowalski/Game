#include "Application.h"

void soundThreadCall(Application::SoundThreadInfo* h)
{
    h->thisHandler->attachTileSounds(*h->deltaTime, *h->cameraView, *h->tilemap);
}
/*void inputThreadCall(TileSoundHandler::ThreadInfo* h)
{
    h->thisHandler->attachTileSounds(*h->deltaTime, *h->cameraView, *h->tilemap);
}*/
void drawThreadCall(Application::DrawThreadInfo* h)
{
    h->renderer->updateTransform(h->mapBank->getTransform(), 1);
    std::vector<sf::Texture> textures = h->mapBank->getTextures();
    h->renderer->updateTexture(textures.at(0), 1);
    h->renderer->updateTexture(textures.at(1), 4);
    h->renderer->updateTexture(textures.at(2), 5);
    std::vector<sf::VertexArray> verticies = h->mapBank->getVerticies();
    h->renderer->updateVerticies(verticies.at(0), 1);
    h->renderer->updateVerticies(verticies.at(1), 2);
    h->renderer->updateVerticies(verticies.at(2), 3);
    h->renderer->updateVerticies(verticies.at(3), 4);
    h->renderer->updateVerticies(verticies.at(4), 5);
    h->renderer->updateVerticies(verticies.at(5), 6);
    h->renderer->updateVerticies(verticies.at(6), 7);
    h->window->m_RenderWindow.clear(sf::Color(255, 0, 255));
    h->window->m_RenderWindow.draw(*h->renderer);
    h->window->m_RenderWindow.display();
}
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
        EventBus::get().update();

		// Cache change in time since last frame
		sf::Time deltaTime = m_Clock.getDeltaTime();

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

		std::vector<Character*> reachables = m_Maps.getCurrMap().second->getReachableCharacters();
		if(reachables.size() > 0)
			m_Window->m_RenderWindow.setTitle(sf::String(std::to_string(m_Clock.getFPS())) + " | " + reachables.at(reachables.size()-1)->getName());
		else m_Window->m_RenderWindow.setTitle(sf::String(std::to_string(m_Clock.getFPS())) + " | " + m_Maps.getCurrMap().first->getName());

		m_Window->m_RenderWindow.setView(m_Camera->getView());

		m_Maps.update(deltaTime, m_Maps.getCurrMap().second->getPlayer()->getCenterPosition(),m_Camera->getBounds());
        
        //background.startMusic();
        background.setVolume(100.0f);
        m_Settings->setEffectsVolume(100.0f);
        
        DrawThreadInfo* d = new DrawThreadInfo;
        d->mapBank  = &m_Maps;
        d->renderer = &m_Renderer;
        d->window   = m_Window;
        sf::Thread drawThread(drawThreadCall, d);
        drawThread.launch();

		// Draw graphics
        
        SoundThreadInfo* s = new SoundThreadInfo;
        s->thisHandler = &TileSoundHandler::get();
        s->deltaTime   = &deltaTime;
        s->cameraView  = &m_Camera->getBounds();
        s->tilemap     = m_Maps.getCurrMap().first;
        sf::Thread soundThread(soundThreadCall, s);
        soundThread.launch();
        
        
        soundThread.wait();
        drawThread.wait();
	}

	return EXIT_SUCCESS;
}

bool Application::init() {
	m_Settings = new Settings();
    m_Settings->setMusicVolume(50.0f);
    m_Settings->setEffectsVolume(50.0f);
    m_Maps.soundInit(m_Settings->getEffectsVolume());
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

}

void Application::toggleFullscreen() {
	m_Settings->toggleFullscreen();

	// Cache current video mode
	sf::VideoMode mode = m_Settings->getCurrVideoMode();

	m_Camera->resize(sf::Vector2f(static_cast<float>(mode.width), static_cast<float>(mode.height)));

	m_Window->toggleFullscreen(m_Settings->getCurrVideoMode(),m_Camera->getView(),m_Settings->isFullscreen());
}

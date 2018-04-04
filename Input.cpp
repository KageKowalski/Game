#include "Input.h"

Input::Input() {
	EventBus::get().registerListener(Event::EventType::EV_LOADMAP, this);
}

Input::~Input() {}

void Input::analyze(GameState state) {
	std::unique_ptr<Event> eventPtr;

	// HANDLE THE FOLLOWING <ALWAYS>:
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F11)) {
		eventPtr = std::make_unique<FullscreenEvent>();
		EventBus::get().postEvent(eventPtr);
	}

	// HANDLE THE FOLLOWING <ON FREEROAM>:
	if (state == GameState::FREEROAM) {
		sf::Vector2f playerCenterPos = Player::get().getCenterPosition();
		bool run = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) {
			eventPtr = std::make_unique<InteractEvent>();
			EventBus::get().postEvent(eventPtr);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {

			run ? eventPtr = std::make_unique<RunUpEvent>(Player::get().getID()) : eventPtr = std::make_unique<WalkUpEvent>(Player::get().getID());

			EventBus::get().postEvent(eventPtr);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {

			run ? eventPtr = std::make_unique<RunLeftEvent>(Player::get().getID()) : eventPtr = std::make_unique<WalkLeftEvent>(Player::get().getID());

			EventBus::get().postEvent(eventPtr);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {

			run ? eventPtr = std::make_unique<RunDownEvent>(Player::get().getID()) : eventPtr = std::make_unique<WalkDownEvent>(Player::get().getID());

			EventBus::get().postEvent(eventPtr);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {

			run ? eventPtr = std::make_unique<RunRightEvent>(Player::get().getID()) : eventPtr = std::make_unique<WalkRightEvent>(Player::get().getID());

			EventBus::get().postEvent(eventPtr);
		}
	}
}

void Input::handleEvent(Event* const e) {
	switch (e->getType()) {
	case Event::EventType::EV_LOADMAP:
		break;
	}
}

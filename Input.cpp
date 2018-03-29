#include "Input.h"

Input::Input() {
	m_MovementMapRef = nullptr;

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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
			if (m_MovementMapRef[static_cast<int>(playerCenterPos.x) / 16][static_cast<int>(playerCenterPos.y - 1.0f) / 16] == 1
				&& sqrt(pow(playerCenterPos.y - (static_cast<int>(playerCenterPos.y - 16.0f) + 8.0f), 2)) <= 16.0f)
			{
				eventPtr = std::make_unique<TurnUpEvent>();
				EventBus::get().postEvent(eventPtr);
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {


			run ? eventPtr = std::make_unique<RunLeftEvent>() : eventPtr = std::make_unique<WalkLeftEvent>();
			EventBus::get().postEvent(eventPtr);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {


			run ? eventPtr = std::make_unique<RunDownEvent>() : eventPtr = std::make_unique<WalkDownEvent>();
			EventBus::get().postEvent(eventPtr);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {


			run ? eventPtr = std::make_unique<RunRightEvent>() : eventPtr = std::make_unique<WalkRightEvent>();
			EventBus::get().postEvent(eventPtr);
		}
	}
}

void Input::handleEvent(Event* const e) {
	switch (e->getType()) {
	case Event::EventType::EV_LOADMAP:
		m_MovementMapRef = dynamic_cast<LoadMapEvent*>(e)->getMovementMap();
		break;
	}
}

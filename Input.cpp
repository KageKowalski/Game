#include "Input.h"

Input::Input() {}

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

		bool run = false;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) && Player::get().getStamina()) {
            run = true;
            Player::get().decrementStamina();
        }

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) {
			eventPtr = std::make_unique<InteractEvent>();
			EventBus::get().postEvent(eventPtr);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {

			run ? eventPtr = std::make_unique<RunEvent>(Player::get().getID(), Direction::UP)
				: eventPtr = std::make_unique<WalkEvent>(Player::get().getID(), Direction::UP);

			EventBus::get().postEvent(eventPtr);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {

			run ? eventPtr = std::make_unique<RunEvent>(Player::get().getID(), Direction::DOWN)
				: eventPtr = std::make_unique<WalkEvent>(Player::get().getID(), Direction::DOWN);

			EventBus::get().postEvent(eventPtr);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {

			run ? eventPtr = std::make_unique<RunEvent>(Player::get().getID(), Direction::LEFT)
				: eventPtr = std::make_unique<WalkEvent>(Player::get().getID(), Direction::LEFT);

			EventBus::get().postEvent(eventPtr);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {

			run ? eventPtr = std::make_unique<RunEvent>(Player::get().getID(), Direction::RIGHT)
				: eventPtr = std::make_unique<WalkEvent>(Player::get().getID(), Direction::RIGHT);

			EventBus::get().postEvent(eventPtr);
		}
	}
}

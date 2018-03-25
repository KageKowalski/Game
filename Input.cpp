#include "Input.h"

Input::Input() {}

Input::~Input() {}

void Input::analyze(GameState state) {
	std::unique_ptr<Event> eventPtr;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F11)) {
		eventPtr = std::make_unique<FullscreenEvent>();
		EventBus::get().postEvent(eventPtr);
	}

	bool run = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
		run ? eventPtr = std::make_unique<RunUpEvent>() : eventPtr = std::make_unique<WalkUpEvent>();
		EventBus::get().postEvent(eventPtr);
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
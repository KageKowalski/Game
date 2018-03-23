#include "Input.h"

Input::Input() {
	m_ToggleFullscreen = sf::Keyboard::Key::F11;
	m_MoveSelectionDown = sf::Keyboard::Key::Down;
	m_MoveSelectionUp = sf::Keyboard::Key::Up;
	m_MoveSelectionLeft = sf::Keyboard::Key::Left;
	m_MoveSelectionRight = sf::Keyboard::Key::Right;
	m_MoveDown = sf::Keyboard::Key::S;
	m_MoveUp = sf::Keyboard::Key::W;
	m_MoveLeft = sf::Keyboard::Key::A;
	m_MoveRight = sf::Keyboard::Key::D;
}

Input::~Input() {}

std::vector<AbstractKeyPressed> Input::fetch() {
	std::vector<AbstractKeyPressed> keysDown;

	if (sf::Keyboard::isKeyPressed(m_ToggleFullscreen)) keysDown.push_back(AbstractKeyPressed::TOGGLE_FULLSCREEN);
	if (sf::Keyboard::isKeyPressed(m_MoveSelectionDown)) keysDown.push_back(AbstractKeyPressed::MOVE_SELECTION_DOWN);
	if (sf::Keyboard::isKeyPressed(m_MoveSelectionUp)) keysDown.push_back(AbstractKeyPressed::MOVE_SELECTION_UP);
	if (sf::Keyboard::isKeyPressed(m_MoveSelectionLeft)) keysDown.push_back(AbstractKeyPressed::MOVE_SELECTION_LEFT);
	if (sf::Keyboard::isKeyPressed(m_MoveSelectionRight)) keysDown.push_back(AbstractKeyPressed::MOVE_SELECTION_RIGHT);
	if (sf::Keyboard::isKeyPressed(m_MoveSelectionDown)) keysDown.push_back(AbstractKeyPressed::MOVE_DOWN);
	if (sf::Keyboard::isKeyPressed(m_MoveSelectionUp)) keysDown.push_back(AbstractKeyPressed::MOVE_UP);
	if (sf::Keyboard::isKeyPressed(m_MoveSelectionLeft)) keysDown.push_back(AbstractKeyPressed::MOVE_LEFT);
	if (sf::Keyboard::isKeyPressed(m_MoveSelectionRight)) keysDown.push_back(AbstractKeyPressed::MOVE_RIGHT);

	return keysDown;
}
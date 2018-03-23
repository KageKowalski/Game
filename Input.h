#ifndef INPUT_H
#define INPUT_H

#include <SFML/Window.hpp>
#include <vector>

enum class AbstractKeyPressed {
	TOGGLE_FULLSCREEN,
	MOVE_SELECTION_DOWN,
	MOVE_SELECTION_UP,
	MOVE_SELECTION_LEFT,
	MOVE_SELECTION_RIGHT,
	MOVE_UP,
	MOVE_DOWN,
	MOVE_LEFT,
	MOVE_RIGHT
};

class Input {
	
public:

	Input();
	~Input();

	std::vector<AbstractKeyPressed> fetch();

private:

	sf::Keyboard::Key m_ToggleFullscreen;
	sf::Keyboard::Key m_MoveSelectionDown;
	sf::Keyboard::Key m_MoveSelectionUp;
	sf::Keyboard::Key m_MoveSelectionLeft;
	sf::Keyboard::Key m_MoveSelectionRight;
	sf::Keyboard::Key m_MoveDown;
	sf::Keyboard::Key m_MoveUp;
	sf::Keyboard::Key m_MoveLeft;
	sf::Keyboard::Key m_MoveRight;

};

#endif
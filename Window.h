#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.hpp>

#include "Settings.h"

class Window {

public:

	Window(const sf::VideoMode& initMode, const sf::View& view, bool fullscreen);
	virtual ~Window();

	// Resizes the viewable area displayed on the render window
	void resize(const sf::View& view);

	// Toggles fullscreen mode
	void toggleFullscreen(const Settings* settings, const sf::View view);

private:

	// Constructs the render window
	void construct(const sf::VideoMode& initMode, const sf::View& view, bool fullscreen);

public:

	// Application window to render onto
	sf::RenderWindow m_RenderWindow;

};

#endif
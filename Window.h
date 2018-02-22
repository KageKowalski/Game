// Klayton Kowalski

#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.hpp>
#include "Settings.h"

// Wrapper class for a render window, which is just a window that can be drawn onto.
// The main application window (with a title bar, maximize, minimize, and exit buttons)
// is an example of what you would use this class for.
class Window {

public:

	// Constructor takes a video mode, a view, and a fullscreen boolean.
	// The video mode can be extracted from the current video mode in Settings,
	// the view can be extracted from the Camera, and fullscreen can also be
	// extracted from Settings.
	Window(const sf::VideoMode& initMode, const sf::View& view, bool fullscreen);
	virtual ~Window();

	// Updates the window's active viewport. The view can be extracted from the current
	// video mode in Settings.
	void resize(const sf::View& view);

	// Calls construct() to construct a new window with toggled fullscreen mode.
	// The video mode can be extracted from the current video mode in Settings,
	// the view can be extracted from the Camera, and fullscreen can also be
	// extracted from Settings.
	void toggleFullscreen(const sf::VideoMode& initMode, const sf::View& view, bool fullscreen);

private:

	// Constructs the render window, closing the current window if it already exists.
	// The video mode can be extracted from the current video mode in Settings,
	// the view can be extracted from the Camera, and fullscreen can also be
	// extracted from Settings.
	void construct(const sf::VideoMode& initMode, const sf::View& view, bool fullscreen);

public:

	// Application window to render onto
	// This is public because we are constantly needing to access it outside of this class,
	// so going through a getter function over and over again would add some unnecessary overhead.
	sf::RenderWindow m_RenderWindow;

};

#endif
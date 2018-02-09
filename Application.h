#ifndef APPLICATION_H
#define APPLICATION_H

#include <SFML/System.hpp>

#include "Window.h"
#include "Settings.h"
#include "Camera.h"
#include "Chrono.h"
#include "Console.h"

class Application {

public:

	Application();
	~Application();

	// Runs the game loop
	int run();

private:

	// Init application
	bool init();

	// Toggle fullscreen mode
	void toggleFullscreen();

private:

	// Physical window
	Window* m_Window;

	// Settings
	Settings* m_Settings;

	// Viewable area
	Camera* m_Camera;

	// Content of physical window
	Console* m_Console;

	// High-performance clock
	Chrono m_Clock;

};

#endif
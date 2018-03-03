#ifndef APPLICATION_H
#define APPLICATION_H

#include <SFML/System.hpp>

#include "Window.h"
#include "Settings.h"
#include "Camera.h"
#include "Chrono.h"
#include "Character.h"
#include "Renderer.h"
#include "Player.h"
#include "SpriteMap.h"
#include "Music.h"

class Application {

public:

	Application();
	~Application();

	// Runs the game loop
	int run();

private:

	// Init application
	bool init();

	// Update components
	void update();

	// Draw graphics
	void draw();

	// Toggle fullscreen mode
	void toggleFullscreen();

private:

	// Physical window
	Window* m_Window;

	// Settings
	Settings* m_Settings;

	// Viewable area
	Camera* m_Camera;

	// Renderer
	Renderer m_Renderer;

	// High-performance clock
	Chrono m_Clock;

};

#endif

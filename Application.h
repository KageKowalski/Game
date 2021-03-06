#ifndef APPLICATION_H
#define APPLICATION_H

#include <SFML/System.hpp>

#include "Window.h"
#include "Settings.h"
#include "Camera.h"
#include "Chrono.h"
#include "Renderer.h"
#include "Music.h"
#include "MapDirector.h"
#include "EventBus.h"
#include "GameState.h"
#include "Input.h"
#include "TextBank.h"
#include "Log.h"

class Application : public EventListener {

public:

	Application();
	virtual ~Application();

	// Runs the game loop
	int run();

	// Handles events pertaining to macro operation in Application
	void handleEvent(Event* const e) override;
    
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

	// Viewable area
	Camera* m_Camera;

	// Renderer
	Renderer m_Renderer;

	// High-performance clock
	Chrono* m_Clock;

	// Current state of the game
	GameState m_State;

	// Input module
	Input m_Input;
    
};

#endif

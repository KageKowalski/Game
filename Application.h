#ifndef APPLICATION_H
#define APPLICATION_H

#include <SFML/System.hpp>
#include <thread>

#include "Window.h"
#include "Settings.h"
#include "Camera.h"
#include "Chrono.h"
#include "Renderer.h"
#include "Music.h"
#include "MapBank.h"
#include "EventBus.h"
#include "GameState.h"
#include "Input.h"
#include "FullLoading.h"

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
    
public:

    struct SoundThreadInfo
    {
        TileSoundHandler*    thisHandler;
        const sf::Time*              deltaTime;
        const sf::FloatRect*  cameraView;
        TileMap*                 tilemap;
    };
    struct DrawThreadInfo
    {
        Window*     window;
        Renderer* renderer;
        MapBank*   mapBank;
    };

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
	Chrono* m_Clock;

	// Current state of the game
	GameState m_State;

	// Input module
	Input m_Input;
    
};

#endif

#ifndef APPLICATION_H
#define APPLICATION_H

#include <SFML/System.hpp>

#include "Window.h"
#include "Settings.h"
#include "Camera.h"
#include "Chrono.h"
#include "Renderer.h"
#include "Music.h"
#include "MapBank.h"
#include "EventBus.h"
#include <thread>

enum class GameState {
	FREEROAM
};

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
    
public:

    struct SoundThreadInfo
    {
        TileSoundHandler*    thisHandler;
        sf::Time*              deltaTime;
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

	// All maps
	MapBank m_Maps;

	// Current state of the game
	GameState m_State;
    
};

#endif

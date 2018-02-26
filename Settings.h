#ifndef SETTINGS_H
#define SETTINGS_H

#include <SFML/Window.hpp>

class Settings {

public:

	Settings(const sf::VideoMode& initMode = sf::VideoMode(800, 600));
	~Settings();

	// Mutators
	void toggleFullscreen();
	void setCurrentVideoMode(const sf::VideoMode& mode);

	// Accessors
	const sf::VideoMode& getCurrVideoMode() const;
	const std::vector<sf::VideoMode>& getFullscreenVideoModes() const;
	bool isFullscreen() const;

private:

	// Video mode being used by application
	sf::VideoMode m_CurrVideoMode;

	// List of valid fullscreen video modes
	std::vector<sf::VideoMode> m_FullscreenVideoModes;

	// Is the application in fullscreen mode?
	bool m_Fullscreen;

};

#endif
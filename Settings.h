// Klayton Kowalski

#ifndef SETTINGS_H
#define SETTINGS_H

#include <SFML/Window.hpp>

// Holds all of the application's meta settings.
// Whenever a change is about to be made to render window or to some setting, the values
// in this class should be updated BEFORE any other class. Then, the value that was updated
// should be PULLED FROM this class and updated in other classes.
// It boils down to this: When it comes to settings, no other class should ever be ahead of
// this class. When other classes need settings information, always pull from this class.
class Settings {

public:

	// Constructor takes an initial video mode to specify in which resolution the render
	// window should boot.
	~Settings();

	// Finds the most efficient fullscreen resolution for the user's particular hardware
	// then sets the proper settings for fullscreen mode setup.
	void toggleFullscreen();

	// Sets the intended video mode for render window.
	void setCurrentVideoMode(const sf::VideoMode& mode);

	// Sets the intended music volume. [0.0f, 100.0f]
	void setMusicVolume(float volume);
	
	// Sets the inteded sound effects volume. [0.0f, 100.0f]
	void setEffectsVolume(float volume);

	// Retrieves the current video mode.
	const sf::VideoMode& getCurrVideoMode() const;

	// Retrieves all of the possible fullscreen video modes for the user's particular hardware.
	// The very first video mode of the return vector is the most compatible, and should be used.
	const std::vector<sf::VideoMode>& getFullscreenVideoModes() const;

	// Are we currently in fullscreen mode?
	bool isFullscreen() const;

	// Retrieves the music volume.
	const float& getMusicVolume() const;

	// Retrieves the sound effects volume.
	const float& getEffectsVolume() const;

private:

	// Video mode being used by application
	sf::VideoMode m_CurrVideoMode;

	// List of valid fullscreen video modes
	std::vector<sf::VideoMode> m_FullscreenVideoModes;

	// Is the application in fullscreen mode?
	bool m_Fullscreen;

	// Volume level of music [0.0f, 100.0f]
	float m_MusicVolume;

	// Volume level of sound effects [0.0f, 100.0f]
	float m_EffectsVolume;
    
public:
    
    Settings(Settings const&)        = delete;
    void operator=(Settings const&)  = delete;
    
    static Settings& get()
    {
        static Settings instance;
        return        instance;
    }
private:
    Settings();
};

#endif

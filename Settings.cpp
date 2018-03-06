#include "Settings.h"

Settings::Settings(const sf::VideoMode& initMode) {
	// Display setup
	m_CurrVideoMode = initMode;
	m_FullscreenVideoModes = sf::VideoMode::getFullscreenModes();
	m_Fullscreen = false;
}

Settings::~Settings() {}

void Settings::toggleFullscreen() {
	m_Fullscreen = !m_Fullscreen;

	// If displaying fullscreen, choose best video mode available
	if (m_Fullscreen) m_CurrVideoMode = m_FullscreenVideoModes.at(0);
	// Else, display windowed mode at 800 x 600 pixels
	else m_CurrVideoMode = sf::VideoMode(800, 600);
}

void Settings::setCurrentVideoMode(const sf::VideoMode& mode) {
	m_CurrVideoMode = mode;
}

void Settings::setMusicVolume(float volume) {
	if (volume < 0.0f) m_MusicVolume = 0.0f;
	else if (volume > 100.0f) m_MusicVolume = 100.0f;
	else m_MusicVolume = volume;
}

void Settings::setEffectsVolume(float volume) {
	if (volume < 0.0f) m_EffectsVolume = 0.0f;
	else if (volume > 100.0f) m_EffectsVolume = 100.0f;
	else m_EffectsVolume = volume;
}

const sf::VideoMode& Settings::getCurrVideoMode() const {
	return m_CurrVideoMode;
}

const std::vector<sf::VideoMode>& Settings::getFullscreenVideoModes() const {
	return m_FullscreenVideoModes;
}

bool Settings::isFullscreen() const {
	return m_Fullscreen;
}

const float Settings::getMusicVolume() const {
	return m_MusicVolume;
}

const float Settings::getEffectsVolume() const {
	return m_EffectsVolume;
}

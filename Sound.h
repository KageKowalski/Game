//Josh Seelye
#ifndef Sound_hpp
#define Sound_hpp

#include <SFML/Audio.hpp>

class Sound
{
protected:
    sf::SoundBuffer _buffer;
    sf::Sound       _sound;
    std::string     _filename;
    sf::Time        _soundDelay;
    sf::Time        _elapsedTime;
    float           _radiusFromPlayer;
    float           _lastIterationRadius;
    
public:
    Sound();
    
    void  resetBuffer();
    void  playSound(sf::Time deltaTime);
    bool  setBuffer(std::string filename);
    void  setVolume(float volume);
    const std::string& getFilename() const;
    float getVolume();
    void  incrementVolume();
    void  decrementVolume();
    bool  isPlaying();
    float getRadiusFromPlayer() const;
    void  setRadiusFromPlayer(float radius);
    float getLastRadiusFromPlayer() const;
    void  setLastRadiusFromPlayer();
};
#endif

//Josh Seelye
#ifndef Sound_hpp
#define Sound_hpp

#include <SFML/Audio.hpp>

class Sound
{
private:
    sf::SoundBuffer _buffer;
    sf::Sound       _sound;
    std::string     _filename;
    sf::Time        _soundDelay;
    sf::Time        _elapsedTime;
    
public:
    Sound();
    Sound(std::string filename, sf::Time soundDelay);
    void  playSound(sf::Time deltaTime);
    void  setVolume(float volume);
    float getVolume();
    void  incrementVolume();
    void  decrementVolume();
    
};
#endif

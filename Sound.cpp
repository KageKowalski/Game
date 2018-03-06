//  Created by Joshua Seelye on 2/28/18.
#include "Sound.h"

Sound::Sound()
{
    _sound.~Sound();
}

Sound::Sound(std::string filename, sf::Time soundDelay) : _filename(filename)
{
    _buffer.loadFromFile(filename);
    _sound.setBuffer(_buffer);
    _soundDelay = soundDelay + _buffer.getDuration();
}
void Sound::playSound(sf::Time deltaTime)
{
    _elapsedTime += deltaTime;
    if(_elapsedTime > _soundDelay)
    {
        _sound.play();
        _elapsedTime = sf::Time::Zero;
    }
}
void Sound::setVolume(float volume)
{
    _sound.setVolume(volume);
}
float Sound::getVolume()
{
    return _sound.getVolume();
}
void  Sound::incrementVolume()
{
    _sound.setVolume(_sound.getVolume()+1.0f);
}
void Sound::decrementVolume()
{
    _sound.setVolume(_sound.getVolume()-1.0f);
}

//  Created by Joshua Seelye on 2/28/18.
#include "Sound.h"

Sound::Sound()
{}
void Sound::playSound(sf::Time deltaTime)
{
    _elapsedTime += deltaTime;
    if(_elapsedTime > _soundDelay && _sound.getStatus() != sf::Sound::Playing)
    {
        _sound.setBuffer(_buffer);
        _sound.play();
        _elapsedTime = sf::Time::Zero;
    }
}
bool Sound::setBuffer(std::string filename)
{
    _filename = filename;
    if(!_buffer.loadFromFile(filename)) return false;
    _soundDelay = _buffer.getDuration();
    return true;
}
void Sound::resetBuffer()
{
    _buffer = sf::SoundBuffer();
}
const std::string& Sound::getFilename() const
{
    return _filename;
}
void Sound::setVolume(float volume)
{
    if(volume <= 0.0f)_sound.setVolume(0.0f);
    else if(volume >= 100.0f) _sound.setVolume(100.0f);
    else _sound.setVolume(volume);
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
bool Sound::isPlaying()
{
    return _sound.getStatus() == _sound.Playing;
}
float Sound::getRadiusFromPlayer() const
{
    return _radiusFromPlayer;
}
void Sound::setRadiusFromPlayer(float radius)
{
    _radiusFromPlayer = radius;
}
float Sound::getLastRadiusFromPlayer() const
{
    return _lastIterationRadius;
}
void Sound::setLastRadiusFromPlayer()
{
    _lastIterationRadius = _radiusFromPlayer;
}

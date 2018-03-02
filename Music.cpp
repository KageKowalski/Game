//  Created by Joshua Seelye on 2/28/18.
#include "Music.h"

Music::Music(std::string filename)
{
    _filename = filename;
    _background.openFromFile(filename);
}

sf::Music& Music::getMusic()
{
    return _background;
}
void Music::setMusic(std::string filename)
{
    if(filename != _filename)
    {
        _background.openFromFile(filename);
        _filename = filename;
    }
}
void Music::startMusic()
{
    if(_background.getStatus() == _background.Stopped) _background.play();
}
void Music::stopMusic()
{
    _background.stop();
}

void Music::setPitch(float j)
{
    _background.setPitch(j);
}

void Music::setVolume(float volume)
{
    _background.setVolume(volume);
}
float Music::getVolume()
{
    return _background.getVolume();
}
void Music::incrementVolume()
{
    _background.setVolume(_background.getVolume()+1.0f);
}
void Music::decrementVolume()
{
    _background.setVolume(_background.getVolume()-1.0f);
}

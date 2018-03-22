//  Created by Joshua Seelye on 3/6/18.
#include "SoundHandler.h"

SoundHandler::SoundHandler()
{}
SoundHandler::~SoundHandler(){}

int SoundHandler::findSound(std::string filename)
{
    int location = -1;
    for(int i = 0; i < 32; i++)
    {
        if(_sounds[i].getFilename()==filename)
        {
            location = i;
            break;
        }
    }
    return location;
}
const Sound* SoundHandler::getSounds()
{
    return _sounds;
}
void SoundHandler::setVolume(const float& volume)
{
    _volume = &volume;
}

void SoundHandler::setLastRadius()
{
    for(int i = 0; i < 32; i++)
    {
        _sounds[i].setLastRadiusFromPlayer();
    }
}

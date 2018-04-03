//  Created by Joshua Seelye on 3/6/18.
#ifndef SoundHandler_hpp
#define SoundHandler_hpp

#include "Sound.h"
#include <SFML/Graphics.hpp>
#include "EventBus.h"

class SoundHandler
{
protected:
    Sound   _sounds[32];
    const float*  _volume;
    
public:
    SoundHandler();
    ~SoundHandler();
    int findSound(std::string filename);
    void setVolume(const float& volume);
    void setLastRadius();
    const Sound* getSounds();
    
};

#endif

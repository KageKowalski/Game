//  Created by Joshua Seelye on 3/6/18.
#ifndef TileSoundHandler_hpp
#define TileSoundHandler_hpp

#include "SoundHandler.h"
#include <SFML/Graphics.hpp>
#include <math.h>
#include <thread>
#include "Player.h"

class TileSoundHandler : public SoundHandler
{
public:
    TileSoundHandler(TileSoundHandler const&)        = delete;
    void operator=(TileSoundHandler const&)  = delete;
    
    static TileSoundHandler& get()
    {
        static TileSoundHandler instance;
        return        instance;
    }
    bool attachTileSounds(sf::Vector2f tilePos, char properties, std::string name);
    bool checkThreadSemaphore();
private:
    TileSoundHandler();
    ~TileSoundHandler();

    void playSounds(sf::Vector2f tilePos, char properties, std::string name);
    
    uint8_t      _tileProperties[32];
    sf::Vector2f _soundsPosition[32];
    sf::Vector2f      _prevPposition;
    sf::Time            _elapsedTime;
    bool                  _threadSemaphore;
    
};

#endif

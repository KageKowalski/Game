//  Created by Joshua Seelye on 3/6/18.
#ifndef TileSoundHandler_hpp
#define TileSoundHandler_hpp

#include "SoundHandler.h"
#include "TileMap.h"
#include <SFML/Graphics.hpp>
#include <math.h>
#include "TileSoundHandler.h"
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
    bool attachTileSounds(sf::Time deltaTime, sf::FloatRect cameraView, TileMap& tilemap, sf::Vector2f pposition );
    bool checkThreadSemaphore();
private:
    TileSoundHandler();
    ~TileSoundHandler();

    void playSounds(sf::Time deltaTime, sf::FloatRect, sf::Vector2f);
    
    virtual void handleEvent(Event* const e);
    uint8_t      _tileProperties[32];
    sf::Vector2f _soundsPosition[32];
    sf::Vector2f      _prevPposition;
    sf::Time            _elapsedTime;
    bool                  _threadSemaphore;
    
};

#endif

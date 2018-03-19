//  Created by Joshua Seelye on 3/6/18.
#ifndef TileSoundHandler_hpp
#define TileSoundHandler_hpp

#include "SoundHandler.h"
#include "TileMap.h"
#include <SFML/Graphics.hpp>
#include <math.h>

class TileSoundHandler : public SoundHandler
{
public:
    TileSoundHandler();
    ~TileSoundHandler();
    bool attachTileSounds(sf::Time deltaTime, sf::FloatRect cameraView, const sf::Vector2f& pposition, const TileMap& tilemap );
private:
    void playSounds(sf::Time deltaTime, sf::FloatRect, const sf::Vector2f&);
    
    uint8_t      _tileProperties[32];
    sf::Vector2f _soundsPosition[32];
    sf::Vector2f      _prevPposition;
    sf::Time            _elapsedTime;
};

#endif

//  Created by Joshua Seelye on 3/6/18.
#include "TileSoundHandler.h"

TileSoundHandler::TileSoundHandler()
{
}
TileSoundHandler::~TileSoundHandler(){}
bool TileSoundHandler::attachTileSounds(sf::Time deltaTime, sf::FloatRect cameraView, TileMap& tilemap, sf::Vector2f pposition )
{
    _elapsedTime += deltaTime;
    for(int i = 0; i < tilemap.getHeight(); i++)
    {
        for(int j = 0; j < tilemap.getWidth(); j++)
        {
//            if(cameraView.contains(tilemap.getGroundTiles()[i][j].getCenterPosition().x*7.0f, tilemap.getGroundTiles()[i][j].getCenterPosition().y*7.0f))
//            {
                if(tilemap.getGroundTiles()[i][j].getSoundFilename().length())
                {
                    if(tilemap.getGroundTiles()[i][j].getProperties() & 0x04)
                    {
                        if(findSound(tilemap.getGroundTiles()[i][j].getSoundFilename()) > -1)
                        {
                            
                            float radius = sqrt(pow(pposition.x-tilemap.getGroundTiles()[i][j].getCenterPosition().x,2)+pow(pposition.y-tilemap.getGroundTiles()[i][j].getCenterPosition().y,2));
                            if(radius < _sounds[findSound(tilemap.getGroundTiles()[i][j].getSoundFilename())].getRadiusFromPlayer() && _soundsPosition[findSound(tilemap.getGroundTiles()[i][j].getSoundFilename())] != tilemap.getGroundTiles()[i][j].getCenterPosition())
                            {
                                _sounds[findSound(tilemap.getGroundTiles()[i][j].getSoundFilename())].setRadiusFromPlayer(radius);
                                _soundsPosition[findSound(tilemap.getGroundTiles()[i][j].getSoundFilename())].x = tilemap.getGroundTiles()[i][j].getCenterPosition().x;
                                _soundsPosition[findSound(tilemap.getGroundTiles()[i][j].getSoundFilename())].y = tilemap.getGroundTiles()[i][j].getCenterPosition().y;
                            }
                            else if(radius != _sounds[findSound(tilemap.getGroundTiles()[i][j].getSoundFilename())].getRadiusFromPlayer()&& _soundsPosition[findSound(tilemap.getGroundTiles()[i][j].getSoundFilename())] == tilemap.getGroundTiles()[i][j].getCenterPosition())
                            {
                                _sounds[findSound(tilemap.getGroundTiles()[i][j].getSoundFilename())].setRadiusFromPlayer(radius);
                            }
                        }
                        else
                        {
                            int count = 0;
                            while(_sounds[count].isPlaying()) count++;
                            float radius = sqrt(pow(pposition.x-tilemap.getGroundTiles()[i][j].getCenterPosition().x,2)+pow(pposition.y-tilemap.getGroundTiles()[i][j].getCenterPosition().y,2));
                            _tileProperties[count] = tilemap.getGroundTiles()[i][j].getProperties();
                            _sounds[count].setRadiusFromPlayer(radius);
                            _soundsPosition[count].x = tilemap.getGroundTiles()[i][j].getCenterPosition().x;
                            _soundsPosition[count].y = tilemap.getGroundTiles()[i][j].getCenterPosition().y;
                            _sounds[count].setBuffer(tilemap.getGroundTiles()[i][j].getSoundFilename());
                        }
                    }
                    if(tilemap.getGroundTiles()[i][j].getProperties() & 0x02)
                    {
                        if(abs(pposition.x-tilemap.getGroundTiles()[i][j].getCenterPosition().x) <= 8 && abs(pposition.y+8.0f-tilemap.getGroundTiles()[i][j].getCenterPosition().y) <= 8)
                        {
                            if(findSound(tilemap.getGroundTiles()[i][j].getSoundFilename()) > -1)
                            {
                                _soundsPosition[findSound(tilemap.getGroundTiles()[i][j].getSoundFilename())].x = tilemap.getGroundTiles()[i][j].getCenterPosition().x;
                                _soundsPosition[findSound(tilemap.getGroundTiles()[i][j].getSoundFilename())].y = tilemap.getGroundTiles()[i][j].getCenterPosition().y;
                            }
                            else
                            {
                                int count = 0;
                                while(_sounds[count].isPlaying()) count++;
                                _tileProperties[count] = tilemap.getGroundTiles()[i][j].getProperties();
                                _sounds[count].setRadiusFromPlayer(0);
                                _soundsPosition[count].x = tilemap.getGroundTiles()[i][j].getCenterPosition().x;
                                _soundsPosition[count].y = tilemap.getGroundTiles()[i][j].getCenterPosition().y;
                                _sounds[count].setBuffer(tilemap.getGroundTiles()[i][j].getSoundFilename());
                            }
                        }
                    }
                }
           // }
            if(cameraView.contains(tilemap.getLayerTwoTiles()[i][j].getCenterPosition().x, tilemap.getLayerTwoTiles()[i][j].getCenterPosition().y))
            {
                
            }
            if(cameraView.contains(tilemap.getLayerThreeTiles()[i][j].getCenterPosition().x, tilemap.getLayerThreeTiles()[i][j].getCenterPosition().y))
            {
                
            }
        }
    }
    playSounds(deltaTime, cameraView, pposition);
    setLastRadius();
	return true;
}

void TileSoundHandler::playSounds(sf::Time deltaTime, sf::FloatRect cameraView, sf::Vector2f pposition)
{
    for(int i = 0; i < 32; i++)
    {
//        if(!(_sounds[i].isPlaying()) && _elapsedTime.asSeconds() > 5.0f && _sounds[i].getFilename().length() > 1)
//        {
//            _sounds[i].resetBuffer();
//            _soundsPosition[i].x = 0;
//            _soundsPosition[i].y = 0;
//            _tileProperties[i]   = 0;
//            _elapsedTime = sf::Time::Zero;
//        }
        if(_tileProperties[i] & 0x04 && *_volume - 1.2f*_sounds[i].getRadiusFromPlayer() > -80.0f)
        {
            _sounds[i].setVolume(*_volume - 1.5f*_sounds[i].getRadiusFromPlayer());
            _sounds[i].playSound(deltaTime);
        }
        if(_tileProperties[i] & 0x02 && pposition != _prevPposition && abs(pposition.x-_soundsPosition[i].x) <= 8 && abs(pposition.y+8.0f-_soundsPosition[i].y) <= 8)
        {
            _sounds[i].setVolume(*_volume);
            _sounds[i].playSound(deltaTime);
        }
    }
    _prevPposition = pposition;
}

bool TileSoundHandler::checkThreadSemaphore()
{
    if(_threadSemaphore)
    {
        _threadSemaphore = false;
        return true;
    }
    return false;
}
void TileSoundHandler::handleEvent(Event* const e)
{
    if(e->getType() == Event::EventType::EV_CREATETHREADS)
        
        _threadSemaphore = true;
}











//  Created by Joshua Seelye on 3/6/18.
#include "TileSoundHandler.h"

TileSoundHandler::TileSoundHandler()
{
}
TileSoundHandler::~TileSoundHandler(){}
bool TileSoundHandler::attachTileSounds(sf::Vector2f tilePos, char properties, std::string name)
{
    _elapsedTime += Chrono::get().getDeltaTime();
    if(name.length())
    {
        if(properties & 0x04)
        {
            if(findSound(name) > -1)
            {
                float radius = sqrt(pow(Player::get().getCenterPosition().x - tilePos.x,2)+pow(Player::get().getCenterPosition().y - tilePos.y,2));
                if(radius < _sounds[findSound(name)].getRadiusFromPlayer() && _soundsPosition[findSound(name)] != tilePos)
                {
                    _sounds[findSound(name)].setRadiusFromPlayer(radius);
                    _soundsPosition[findSound(name)].x = tilePos.x;
                    _soundsPosition[findSound(name)].y = tilePos.y;
                }
                else if(radius != _sounds[findSound(name)].getRadiusFromPlayer()&& _soundsPosition[findSound(name)] == tilePos)
                {
                    _sounds[findSound(name)].setRadiusFromPlayer(radius);
                }
            }
            else
            {
                int count = 0;
                while(_sounds[count].isPlaying()) count++;
                float radius = sqrt(pow(Player::get().getCenterPosition().x-tilePos.x,2)+pow(Player::get().getCenterPosition().y-tilePos.y,2));
                if((*_volume - *_volume * .015*radius) > -80.0f)
                {
                    _tileProperties[count] = properties;
                    _sounds[count].setRadiusFromPlayer(radius);
                    _soundsPosition[count].x = tilePos.x;
                    _soundsPosition[count].y = tilePos.y;
                    _sounds[count].setBuffer(name);
                }
            }
        }
        if(properties & 0x02)
        {
            if(abs(Player::get().getCenterPosition().x-tilePos.x) <= 8 && abs(Player::get().getCenterPosition().y+8.0f-tilePos.y) <= 8)
            {
                if(findSound(name) > -1)
                {
                    _soundsPosition[findSound(name)].x = tilePos.x;
                    _soundsPosition[findSound(name)].y = tilePos.y;
                }
                else
                {
                    int count = 0;
                    while(_sounds[count].isPlaying()) count++;
                    _tileProperties[count] = properties;
                    _sounds[count].setRadiusFromPlayer(0);
                    _soundsPosition[count].x = tilePos.x;
                    _soundsPosition[count].y = tilePos.y;
                    _sounds[count].setBuffer(name);
                }
            }
        }
    }
    playSounds(tilePos, properties, name);
    setLastRadius();
    return true;
}

void TileSoundHandler::playSounds(sf::Vector2f tilePos, char properties, std::string name)
{
    for(int i = 0; i < 32; i++)
    {
        if(_tileProperties[i] & 0x04 && *_volume - *_volume * .015*_sounds[i].getRadiusFromPlayer() < -80.0f)
        {
            _sounds[i] = Sound();
            _soundsPosition[i].x = 0;
            _soundsPosition[i].y = 0;
            _tileProperties[i]   = 0;
            _elapsedTime = sf::Time::Zero;
            _sounds[i].setRadiusFromPlayer(0);
        }
        if(_tileProperties[i] & 0x02 && !(_sounds[i].isPlaying()) && (_elapsedTime.asSeconds() > 5.0f) && (_sounds[i].getFilename().length() > 5))
        {
            _sounds[i] = Sound();
            _soundsPosition[i].x = 0;
            _soundsPosition[i].y = 0;
            _tileProperties[i]   = 0;
            _elapsedTime = sf::Time::Zero;
        }
        if(_tileProperties[i] & 0x04 && *_volume - *_volume * 0.015f *_sounds[i].getRadiusFromPlayer() > -80.0f)
        {
            _sounds[i].setVolume(*_volume - *_volume * 0.01f *_sounds[i].getRadiusFromPlayer());
            _sounds[i].playSound(Chrono::get().getDeltaTime());
        }
        if(_tileProperties[i] & 0x02 && Player::get().getCenterPosition() != _prevPposition && abs(Player::get().getCenterPosition().x-_soundsPosition[i].x) <= 8 && abs(Player::get().getCenterPosition().y+8.0f-_soundsPosition[i].y) <= 8)
        {
            _sounds[i].setVolume(*_volume);
            _sounds[i].playSound(Chrono::get().getDeltaTime());
        }
    }
    _prevPposition = Player::get().getCenterPosition();
}

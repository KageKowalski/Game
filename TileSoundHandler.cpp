//  Created by Joshua Seelye on 3/6/18.
#include "TileSoundHandler.h"

TileSoundHandler::TileSoundHandler()
{
}
TileSoundHandler::~TileSoundHandler(){}
bool TileSoundHandler::attachTileSounds(sf::Time deltaTime, sf::FloatRect cameraView, const sf::Vector2f& pposition, const TileMap& tilemap)
{
	for (int i = 0; i < tilemap.getHeight(); i++)
	{
		for (int j = 0; j < tilemap.getWidth(); j++)
		{
			if (cameraView.contains(tilemap.getGroundTiles()[i][j].getCenterPosition().x * 16.0f, tilemap.getGroundTiles()[i][j].getCenterPosition().y * 16.0f))
			{
				if (tilemap.getGroundTiles()[i][j].getSoundFilename().length())
				{
					if (findSound(tilemap.getGroundTiles()[i][j].getSoundFilename()) > -1)
					{

						float radius = sqrt(pow(abs(pposition.x - tilemap.getGroundTiles()[i][j].getCenterPosition().x), 2) + pow(abs(pposition.y - tilemap.getGroundTiles()[i][j].getCenterPosition().y), 2));
						if (radius < _sounds[findSound(tilemap.getGroundTiles()[i][j].getSoundFilename())].getRadiusFromPlayer() && _soundsPosition[findSound(tilemap.getGroundTiles()[i][j].getSoundFilename())] != tilemap.getGroundTiles()[i][j].getCenterPosition())
						{
							_sounds[findSound(tilemap.getGroundTiles()[i][j].getSoundFilename())].setRadiusFromPlayer(radius);
							_soundsPosition[findSound(tilemap.getGroundTiles()[i][j].getSoundFilename())].x = tilemap.getGroundTiles()[i][j].getCenterPosition().x;
							_soundsPosition[findSound(tilemap.getGroundTiles()[i][j].getSoundFilename())].y = tilemap.getGroundTiles()[i][j].getCenterPosition().y;
						}
						else if (radius != _sounds[findSound(tilemap.getGroundTiles()[i][j].getSoundFilename())].getRadiusFromPlayer() && _soundsPosition[findSound(tilemap.getGroundTiles()[i][j].getSoundFilename())] == tilemap.getGroundTiles()[i][j].getCenterPosition())
						{
							_sounds[findSound(tilemap.getGroundTiles()[i][j].getSoundFilename())].setRadiusFromPlayer(radius);
						}
					}
					else
					{
						int count = 0;
						while (_sounds[count].isPlaying()) count++;
						float radius = sqrt(pow(abs(pposition.x - tilemap.getGroundTiles()[i][j].getCenterPosition().x), 2) + pow(abs(pposition.y - tilemap.getGroundTiles()[i][j].getCenterPosition().y), 2));
						_tileProperties[count] = tilemap.getGroundTiles()[i][j].getProperties();
						_sounds[count].setRadiusFromPlayer(radius);
						_soundsPosition[count].x = tilemap.getGroundTiles()[i][j].getCenterPosition().x;
						_soundsPosition[count].y = tilemap.getGroundTiles()[i][j].getCenterPosition().y;
						_sounds[count].setBuffer(tilemap.getGroundTiles()[i][j].getSoundFilename());
					}
				}
				// }
				if (cameraView.contains(tilemap.getLayerTwoTiles()[i][j].getCenterPosition().x, tilemap.getLayerTwoTiles()[i][j].getCenterPosition().y))
				{

				}
				if (cameraView.contains(tilemap.getLayerThreeTiles()[i][j].getCenterPosition().x, tilemap.getLayerThreeTiles()[i][j].getCenterPosition().y))
				{

				}
			}
		}
		playSounds(deltaTime, cameraView);
		setLastRadius();
		return true;
	}
}

void TileSoundHandler::playSounds(sf::Time deltaTime, sf::FloatRect cameraView)
{
    for(int i = 0; i < 32; i++)
    {
        if(_tileProperties[i] & 0x04)
        {
            //if(cameraView.contains(_soundsPosition[i].x * 7, _soundsPosition[i].y * 7))
            //{
                _sounds[i].setVolume(*_volume - _sounds[i].getRadiusFromPlayer());
                _sounds[i].playSound(deltaTime);
            //}
        }
    }
}


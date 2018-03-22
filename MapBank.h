// Klayton Kowalski

#ifndef MAPBANK_H
#define MAPBANK_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "TileMap.h"
#include "SpriteMap.h"
#include "Player.h"
#include "NPC.h"
#include "TileSoundHandler.h"
#include <thread>
#include "EventBus.h"
#include "Events.h"
#include <memory>
#include <thread>

class MapBank : public sf::Transformable {

public:

	MapBank(const sf::Vector2f& scale);
	~MapBank();

	bool loadMap(int mapID, const float& volume);

	void update(sf::Time deltaTime, const sf::Vector2f& pposition, sf::FloatRect cameraView);

	void setCurrMapID(int mapID);

	std::pair<TileMap*, SpriteMap*>& getCurrMap();
	const sf::Transform& getTransform() const;
	const std::vector<sf::VertexArray>& getVerticies() const;
	const std::vector<sf::Texture>& getTextures() const;

	int getCurrMapID() const;
    void soundInit(const float& volume);

private:

	std::vector<std::pair<TileMap*, SpriteMap*>> m_Maps;

	std::vector<std::string> m_TileSetFileNames;
	std::string m_UniversalSpriteSheetFileName;
	std::vector<std::string> m_LocalSpriteSheetFileNames;
	std::vector<std::string> m_BackgroundMusicFileNames;

	int m_CurrMap;
    
    TileSoundHandler m_SoundHandler;

	std::vector<sf::VertexArray> m_CurrMapVerticies;
	std::vector<sf::Texture> m_CurrMapTextures;

};

#endif

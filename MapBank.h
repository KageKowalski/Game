// Klayton Kowalski

#ifndef MAPBANK_H
#define MAPBANK_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Map.h"
#include "Player.h"
#include "NPC.h"
#include "TileSoundHandler.h"
#include <thread>
#include "EventBus.h"
#include "Events.h"
#include "MapBuilder.h"
#include <memory>
#include <thread>

class MapBank : public sf::Transformable {

public:
    MapBank(MapBank const&)        = delete;
    void operator=(MapBank const&)  = delete;
    
    static MapBank& get()
    {
        static MapBank instance;
        return        instance;
    }
	~MapBank();

	bool loadMap(int mapID);

	void update(sf::FloatRect cameraView);

	void setCurrMapID(int mapID);

	Map* getCurrMap();
	const sf::Transform& getTransform() const;
	const std::vector<sf::VertexArray>& getVerticies() const;
	const std::vector<sf::Texture>& getTextures() const;

	int getCurrMapID() const;
    void soundInit(const float& volume);

private:

	std::vector<Map*> _map;

	std::vector<std::string> m_TileSetFileNames;
	std::string m_UniversalSpriteSheetFileName;
	std::vector<std::string> m_LocalSpriteSheetFileNames;
	std::vector<std::string> m_BackgroundMusicFileNames;
    MapBank();
    
	int m_CurrMap;
    
    TileSoundHandler* m_SoundHandler;

	std::vector<sf::VertexArray> m_CurrMapVerticies;
	std::vector<sf::Texture> m_CurrMapTextures;

	MapBuilder _mapBuilder;

};

#endif

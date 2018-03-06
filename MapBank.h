// Klayton Kowalski

#ifndef MAPBANK_H
#define MAPBANK_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "TileMap.h"
#include "SpriteMap.h"
#include "Player.h"

class MapBank : public sf::Transformable {

public:

	MapBank(const sf::Vector2f& scale);
	~MapBank();

	bool loadMap(int mapID, const float& volume);

	void update(sf::Time deltaTime, const sf::Vector2f& pposition);

	void setCurrMapID(int mapID);

	std::pair<TileMap*, SpriteMap*>& getCurrMap();
	const sf::Transform& getTransform() const;
	const std::vector<sf::VertexArray>& getVerticies() const;
	const std::vector<sf::Texture>& getTextures() const;

	int getCurrMapID() const;

private:

	std::vector<std::pair<TileMap*, SpriteMap*>> m_Maps;

	std::vector<std::string> m_TileSetFileNames;
	std::string m_UniversalSpriteSheetFileName;
	std::vector<std::string> m_LocalSpriteSheetFileNames;
	std::vector<std::string> m_BackgroundMusicFileNames;

	int m_CurrMap;

	std::vector<sf::VertexArray> m_CurrMapVerticies;
	std::vector<sf::Texture> m_CurrMapTextures;

};

#endif

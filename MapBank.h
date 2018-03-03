// Klayton Kowalski

#ifndef MAPBANK_H
#define MAPBANK_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "TileMap.h"
#include "SpriteMap.h"

class MapBank : sf::Transformable {

public:

	MapBank(const sf::Vector2f& scale);
	~MapBank();

	bool loadMap(int mapID);

	const sf::Transform& getTransform() const;
	const std::vector<sf::VertexArray> getVerticies() const;
	const std::vector<sf::Texture> getTextures() const;

private:

	std::vector<std::pair<TileMap*, SpriteMap*>> m_Maps;

	std::vector<std::string> m_TileSetFileNames;
	std::string m_UniversalSpriteSheetFileName;
	std::vector<std::string> m_LocalSpriteSheetFileNames;
	std::vector<std::string> m_BackgroundMusicFileNames;

	int m_CurrMap;

};

#endif
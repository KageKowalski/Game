// Klayton Kowalski

#include "MapBank.h"

MapBank::MapBank(const sf::Vector2f& scale) {
	setScale(scale);

	m_TileSetFileNames.push_back("TestTileSet.png");
	m_UniversalSpriteSheetFileName = "lar.png";
	m_LocalSpriteSheetFileNames.push_back("lar.png");
	m_BackgroundMusicFileNames.push_back("Game_Test.wav");

	m_CurrMap = 0;
}

MapBank::~MapBank() {
	for (size_t i = 0; i < m_Maps.size(); i++) {
		delete m_Maps.at(i).first;
		delete m_Maps.at(i).second;
	}
}

bool MapBank::loadMap(int mapID) {
	if (mapID == 0) {
		TileMap* testMap = new TileMap("Bodybuilder Hamlet");
		SpriteMap* spriteMap = new SpriteMap();
		int blank[1] = { -2 };
		int mapOne[100] =
		{
			13,13,13,13,13,13,13,13,13,13,
			13,1,2,2,2,2,2,2,3,13,
			13,8,0,0,0,0,0,0,4,13,
			13,8,0,0,0,0,0,0,4,13,
			13,8,0,0,0,0,0,0,4,13,
			13,8,0,0,0,0,0,0,4,13,
			13,8,0,0,0,0,0,0,4,13,
			13,8,0,0,0,0,0,0,4,13,
			13,7,6,6,6,6,6,6,5,13,
			13,13,13,13,13,13,13,13,13,13
		};
		if (!testMap->build(mapOne, blank, blank, blank, blank, 10, 10, "Game_Test.wav", "TestTileSet.png"))
			return false;
		
		if (!spriteMap->build("lar.png", "lar.png", std::vector<Character*>()))
			return false;

		std::pair<TileMap*, SpriteMap*> pair;
		pair.first = testMap;
		pair.second = spriteMap;
		m_Maps.push_back(pair);
		return true;
	}

	return false;
}

const sf::Transform& MapBank::getTransform() const {
	return sf::Transformable::getTransform();
}

const std::vector<sf::VertexArray> MapBank::getVerticies() const {
	sf::VertexArray ground = m_Maps.at(m_CurrMap).first->getGroundVertices();
	sf::VertexArray Z2 = m_Maps.at(m_CurrMap).first->getLayerTwoVertices();
	sf::VertexArray Z3 = m_Maps.at(m_CurrMap).first->getLayerThreeVertices();
	sf::VertexArray Z6 = m_Maps.at(m_CurrMap).first->getLayerSixVertices();
	sf::VertexArray canopy = m_Maps.at(m_CurrMap).first->getCanopyVertices();
	sf::VertexArray universal = m_Maps.at(m_CurrMap).second->getUniversalSpriteVerticies();
	sf::VertexArray local = m_Maps.at(m_CurrMap).second->getLocalSpriteVerticies();
	std::vector<sf::VertexArray> retVerticies;
	retVerticies.push_back(ground);
	retVerticies.push_back(Z2);
	retVerticies.push_back(Z3);
	retVerticies.push_back(Z6);
	retVerticies.push_back(canopy);
	retVerticies.push_back(universal);
	retVerticies.push_back(local);
	return retVerticies;
}

const std::vector<sf::Texture> MapBank::getTextures() const {
	std::vector<sf::Texture> retTextures;
	retTextures.push_back(m_Maps.at(m_CurrMap).first->getTileSet());
	retTextures.push_back(m_Maps.at(m_CurrMap).second->getUniversalSpriteSheet());
	retTextures.push_back(m_Maps.at(m_CurrMap).second->getLocalSpriteSheet());
	return retTextures;
}
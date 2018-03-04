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
		
		std::vector<Character*> characters;
		characters.push_back(new Player(sf::Vector2f(0.0f, 0.0f), 0, 4, 16, 32, "Josh smells like my grandmother's penis"));
		if (!spriteMap->build("testplayer.png", "testplayer.png", characters))
			return false;

		std::pair<TileMap*, SpriteMap*> pair;
		pair.first = testMap;
		pair.second = spriteMap;
		m_Maps.push_back(pair);
		return true;
	}

	return false;
}

void MapBank::update(sf::Time deltaTime) {
	TileMap* currTileMap = m_Maps.at(m_CurrMap).first;
	SpriteMap* currSpriteMap = m_Maps.at(m_CurrMap).second;

	currTileMap->updateMap(deltaTime);
	currSpriteMap->update(deltaTime);

	m_CurrMapVerticies.clear();
	m_CurrMapTextures.clear();

	m_CurrMapVerticies.push_back(currTileMap->getGroundVertices());
	m_CurrMapVerticies.push_back(currTileMap->getLayerTwoVertices());
	m_CurrMapVerticies.push_back(currTileMap->getLayerThreeVertices());
	m_CurrMapVerticies.push_back(currSpriteMap->getUniversalSpriteVerticies());
	m_CurrMapVerticies.push_back(currSpriteMap->getLocalSpriteVerticies());
	m_CurrMapVerticies.push_back(currTileMap->getLayerSixVertices());
	m_CurrMapVerticies.push_back(currTileMap->getCanopyVertices());
	m_CurrMapTextures.push_back(currTileMap->getTileSet());
	m_CurrMapTextures.push_back(currSpriteMap->getUniversalSpriteSheet());
	m_CurrMapTextures.push_back(currSpriteMap->getLocalSpriteSheet());
}

void MapBank::setCurrMapID(int mapID) {
	m_CurrMap = mapID;
}

std::pair<TileMap*, SpriteMap*>& MapBank::getCurrMap() {
	return m_Maps.at(m_CurrMap);
}

const sf::Transform& MapBank::getTransform() const {
	return sf::Transformable::getTransform();
}

const std::vector<sf::VertexArray>& MapBank::getVerticies() const {
	return m_CurrMapVerticies;
}

const std::vector<sf::Texture>& MapBank::getTextures() const {
	return m_CurrMapTextures;
}

int MapBank::getCurrMapID() const {
	return m_CurrMap;
}
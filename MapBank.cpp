// Klayton Kowalski

#include "MapBank.h"

MapBank::MapBank(const sf::Vector2f& scale) {
	setScale(scale);
    m_SoundHandler = &TileSoundHandler::get();
	m_TileSetFileNames.push_back("Tileset_1.png");
	m_UniversalSpriteSheetFileName = "UniversalSpriteSheet.png";
	m_LocalSpriteSheetFileNames.push_back("UniversalSpriteSheet.png");
	m_BackgroundMusicFileNames.push_back("Game_Test.wav");

	m_CurrMap = 0;
}

void MapBank::soundInit(const float& volume)
{
    m_SoundHandler->setVolume(volume);
}

MapBank::~MapBank() {
	for (size_t i = 0; i < m_Maps.size(); i++) {
		delete m_Maps.at(i).first;
		delete m_Maps.at(i).second;
	}
}

bool MapBank::loadMap(int mapID, const float &volume) {
	if (mapID == 0) {
		TileMap* testMap = new TileMap("Piglet Hamlet");
		SpriteMap* spriteMap = new SpriteMap();
		int blank[1] = { -2 };
		int layerOne[484] =
		{
            13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,
            13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,
            13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,
            13,13,13,13,13,13,13,24,19,19,25,13,13,13,13,13,13,13,13,13,13,13,
            13,13,13,13,13,13,24,18,26,26,21,13,13,13,13,13,13,13,13,13,13,13,
            13,13,13,13,13,13,17,26,26,26,20,25,13,13,13,13,13,13,13,13,13,13,
            13,13,13,13,13,13,17,26,26,26,26,20,25,13,13,13,13,13,13,13,13,13,
            13,13,13,13,13,24,18,26,26,26,26,26,20,19,19,25,13,13,13,13,13,13,
            13,13,13,13,13,17,26,26,26,26,26,26,26,26,26,20,19,25,13,13,13,13,
            13,13,13,13,24,18,26,26,26,26,26,26,26,26,26,26,26,21,13,13,13,13,
            13,13,13,13,17,26,26,26,26,26,26,26,26,26,26,26,26,21,13,13,13,13,
            13,13,13,13,23,15,15,15,16,26,26,1,3,26,26,26,14,22,13,13,13,13,
            13,13,13,13,13,13,13,13,23,15,15,8,10,3,15,15,22,13,13,13,13,13,
            13,13,13,13,13,13,13,13,13,13,13,7,6,5,13,13,13,13,13,13,13,13,
            13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,
            13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,
            13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,
            13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,
            13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,
            13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,
            13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,
            13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13
		};
		int layerTwo[484] =
		{
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,177,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,134,-1,-1,-1,-1,
            -1,-1,-1,92,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
            -1,-1,-1,-1,-1,92,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
            -1,-1,92,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
            -1,-1,-1,-1,134,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,134,-1,-1,
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,92,-1,-1,-1,-1,-1,-1,-1,-1,
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
		};
        int layerFive[484] =
        {
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
            -1,-1,-1,-1,-1,-1,-1,-1,58,59,60,61,62,-1,-1,-1,-1,-1,-1,-1,-1,-1,
            -1,-1,-1,-1,-1,-1,-1,-1,97,98,99,100,101,-1,-1,-1,-1,-1,-1,-1,-1,-1,
            -1,-1,-1,-1,-1,-1,-1,-1,136,137,138,139,140,-1,-1,-1,55,56,57,-1,-1,-1,
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,94,95,96,-1,-1,-1,
            -1,-1,52,53,54,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
            -1,-1,-1,-1,52,53,54,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
            -1,52,53,54,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
            -1,-1,-1,55,56,57,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
            -1,-1,-1,94,95,96,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,55,56,57,-1,
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,94,95,96,-1,
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,52,53,54,-1,-1,-1,-1,-1,-1,-1,
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1

        };

		if (!testMap->build(layerOne, layerTwo, blank, blank, layerFive, 22, 22, volume, "Game_Test.wav", "Tileset_1.png"))
			return false;
		
		std::vector<Character*> characters;
        characters.push_back(&Player::get());
		characters.push_back(new NPC(sf::Vector2f(60.0f, 60.0f), 0, 24, 16, 32, Behavior::WALK_AROUND, "Near a walking NPC"));
		characters.push_back(new NPC(sf::Vector2f(100.0f, 20.0f), 0, 24, 16, 32, Behavior::LOOK_AROUND_RANDOMLY, "Near a looking NPC"));
		if (!spriteMap->build("UniversalSpriteSheet.png", "UniversalSpriteSheet.png", characters))
			return false;

		std::pair<TileMap*, SpriteMap*> pair;
		pair.first = testMap;
		pair.second = spriteMap;
		m_Maps.push_back(pair);
		return true;
	}

	return false;
}

void MapBank::update(sf::Time deltaTime,const sf::Vector2f& pposition, sf::FloatRect cameraView) {
	TileMap* currTileMap = m_Maps.at(m_CurrMap).first;
	SpriteMap* currSpriteMap = m_Maps.at(m_CurrMap).second;
    
	currTileMap->updateMap(deltaTime, pposition);
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

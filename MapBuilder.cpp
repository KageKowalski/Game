#include "MapBuilder.h"

MapBuilder::MapBuilder() {
	_currMap = nullptr;
}

MapBuilder::~MapBuilder() {
	if (_currMap != nullptr)
		delete _currMap;
}

bool MapBuilder::build(int* groundLayer, int* layerTwo, int* layerThree, int* layerSix, int* canopyLayer,
	int width, int height, const std::string& tilesetFileName, const std::string& universalSpriteSheetFileName,
	const std::string& localSpriteSheetFileName, const std::vector<Character*>& characters,
	const std::string& musicFileName, const std::string& mapName)
{
	if (_currMap != nullptr)
		delete _currMap;

	_currMap = new Map;

	const std::string tilesetFilePath = tilesetFileName;
	const std::string universalSpriteSheetFilePath = universalSpriteSheetFileName;
	const std::string localSpriteSheetFilePath = localSpriteSheetFileName;

	if (!_currMap->_tileset.loadFromFile(tilesetFilePath))
		return false;
	if (!_currMap->_universalSpriteSheet.loadFromFile(universalSpriteSheetFilePath))
		return false;
	if (!_currMap->_localSpriteSheet.loadFromFile(universalSpriteSheetFilePath))
		return false;

	_currMap->_music = musicFileName;

	_currMap->_name = mapName;

	_currMap->_width = width;
	_currMap->_height = height;

	_currMap->_groundVerticies.resize(width * height * 4);
	_currMap->_layerTwoVerticies.resize(width * height * 4);
	_currMap->_layerThreeVerticies.resize(width * height * 4);
	_currMap->_layerSixVerticies.resize(width * height * 4);
	_currMap->_canopyVerticies.resize(width * height * 4);

	_currMap->_characters = characters;

	size_t universalCount = 0;
	size_t localCount = 0;
	for (const Character* const character : characters) {
		if (character->isUniversal()) universalCount++;
		if (character->isUniversal()) localCount++;
	}

	_currMap->_universalSpriteVerticies.resize(universalCount * 4);
	_currMap->_localSpriteVerticies.resize(localCount * 4);

	for (size_t i = 0; i < characters.size(); i++)
		_currMap->spriteVertexFill(characters.at(i), i * 4);

	_currMap->_map = new Map::LayeredTile*[height];
	for (int i = 0; i < height; i++) _currMap->_map[i] = new Map::LayeredTile[width];

	int tileCounter = 0;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {

			Map::LayeredTile* layeredTile = new Map::LayeredTile;

			if (groundLayer[0] != -2) {
				switch (groundLayer[i*width + j]) {
				case 0:
				case 1:
				case 2:
				case 3:
				case 4:
				case 5:
				case 6:
				case 7:
				case 8:
				case 9:
				case 10:
				case 11:
				case 12:
					layeredTile->ground = new Tile(groundLayer[i * width + j], sf::Vector2f(j, i), tileCounter, 0x05, "waves.wav");
					break;
				case 13:
				case 14:
				case 15:
				case 16:
				case 17:
				case 18:
				case 19:
				case 20:
				case 21:
				case 22:
				case 23:
				case 24:
				case 25:
					layeredTile->ground = new Tile(groundLayer[i * width + j], sf::Vector2f(j, i), tileCounter, 0x02, "grass_foot.wav");
					break;
				default:
					layeredTile->ground = new Tile(groundLayer[i * width + j], sf::Vector2f(j, i), tileCounter);
					break;
				}
			}
			else layeredTile->ground = new Tile();

			if (layerTwo[0] != -2) {
				switch (layerTwo[i * width + j]) {
				case 28:
					layeredTile->layerTwo = new Tile(layerTwo[i * width + j], sf::Vector2f(j, i), tileCounter, 0x01);
					break;
				case 92:
					layeredTile->layerTwo = new Tile(layerTwo[i * width + j], sf::Vector2f(j, i), tileCounter, 0x09);
					break;
				default:
					layeredTile->layerTwo = new Tile(layerTwo[i * width + j], sf::Vector2f(j, i), tileCounter);
					break;
				}
			}
			else layeredTile->layerTwo = new Tile();

			if (layerThree[0] != -2) layeredTile->layerThree = new Tile(layerThree[i * width + j], sf::Vector2f(j, i), tileCounter);
			else layeredTile->layerThree = new Tile();

			if (layerSix[0] != -2) layeredTile->layerSix = new Tile(layerSix[i * width + j], sf::Vector2f(j, i), tileCounter);
			else layeredTile->layerSix = new Tile();

			if (canopyLayer[0] != -2) {
				switch (canopyLayer[i * width + j]) {
				case 52:
				case 53:
				case 54:
					layeredTile->canopy = new Tile(canopyLayer[i * width + j], sf::Vector2f(j, i), tileCounter, 0x10);
					break;
				default:
					layeredTile->canopy = new Tile(canopyLayer[i * width + j], sf::Vector2f(j, i), tileCounter);
					break;
				}
			}
			else layeredTile->canopy = new Tile();

			_currMap->_map[i][j] = *layeredTile;
			_currMap->tileVertexFill(i, j);
			tileCounter++;
		}
	}

	return true;
}

Map* MapBuilder::produce() {
	if (_currMap == nullptr)
		return nullptr;

	Map* retMap = &*_currMap;
	_currMap = nullptr;
	return retMap;
}
#include "MapBuilder.h"

bool MapBuilder::Componets::ready() const {
	if (_groundLayer == nullptr) return false;
	if (_layerTwo == nullptr) return false;
	if (_layerThree == nullptr) return false;
	if (_layerSix == nullptr) return false;
	if (_canopyLayer == nullptr) return false;
	if (_width <= 0) return false;
	if (_height <= 0) return false;
	if (_tilesetFileName == nullptr) return false;
	if (_universalSpriteSheetFileName == nullptr) return false;
	if (_localSpriteSheetFileName == nullptr) return false;
	if (_characters == nullptr) return false;
	if (_musicFileName == nullptr) return false;
	if (_mapName == nullptr) return false;

	return true;
}

MapBuilder::MapBuilder() {
	_currMap = nullptr;
}

MapBuilder::~MapBuilder() {
	if (_currMap != nullptr)
		delete _currMap;
}

bool MapBuilder::build(const MapBuilder::Componets& components) {
	if (components.ready() == false)
		return false;

	if (_currMap != nullptr)
		delete _currMap;

	_currMap = new Map;

	const std::string tilesetFilePath = *components._tilesetFileName;
	const std::string universalSpriteSheetFilePath = *components._universalSpriteSheetFileName;
	const std::string localSpriteSheetFilePath = *components._localSpriteSheetFileName;

	if (!_currMap->_tileset.loadFromFile(tilesetFilePath))
		return false;
	if (!_currMap->_universalSpriteSheet.loadFromFile(universalSpriteSheetFilePath))
		return false;
	if (!_currMap->_localSpriteSheet.loadFromFile(universalSpriteSheetFilePath))
		return false;

	_currMap->_music = *components._musicFileName;

	_currMap->_name = *components._mapName;

	_currMap->_width = components._width;
	_currMap->_height = components._height;

	_currMap->_groundVerticies.resize(components._width * components._height * 4);
	_currMap->_layerTwoVerticies.resize(components._width * components._height * 4);
	_currMap->_layerThreeVerticies.resize(components._width * components._height * 4);
	_currMap->_layerSixVerticies.resize(components._width * components._height * 4);
	_currMap->_canopyVerticies.resize(components._width * components._height * 4);

	_currMap->_characters = *components._characters;

	size_t universalCount = 0;
	size_t localCount = 0;
	for (const Character* const character : *components._characters) {
		if (character->isUniversal()) universalCount++;
		if (character->isUniversal()) localCount++;
	}

	_currMap->_universalSpriteVerticies.resize(universalCount * 4);
	_currMap->_localSpriteVerticies.resize(localCount * 4);

	for (size_t i = 0; i < components._characters->size(); i++)
		_currMap->spriteVertexFill(components._characters->at(i), i * 4);

	_currMap->_map = new Map::LayeredTile*[components._height];
	for (int i = 0; i < components._height; i++) _currMap->_map[i] = new Map::LayeredTile[components._width];

	int tileCounter = 0;
	for (int i = 0; i < components._height; i++) {
		for (int j = 0; j < components._width; j++) {

			Map::LayeredTile* layeredTile = new Map::LayeredTile;

			if (components._groundLayer[0] != -2) {
				switch (components._groundLayer[i * components._width + j]) {
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
					layeredTile->ground = new Tile(components._groundLayer[i * components._width + j],
						sf::Vector2f(j, i), tileCounter, 0x05, "waves.wav");
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
					layeredTile->ground = new Tile(components._groundLayer[i * components._width + j],
						sf::Vector2f(j, i), tileCounter, 0x02, "grass_foot.wav");
					break;
				default:
					layeredTile->ground = new Tile(components._groundLayer[i * components._width + j],
						sf::Vector2f(j, i), tileCounter);
					break;
				}
			}
			else layeredTile->ground = new Tile();

			if (components._layerTwo[0] != -2) {
				switch (components._layerTwo[i * components._width + j]) {
				case 28:
					layeredTile->layerTwo = new Tile(components._layerTwo[i * components._width + j],
						sf::Vector2f(j, i), tileCounter, 0x01);
					break;
				case 92:
					layeredTile->layerTwo = new Tile(components._layerTwo[i * components._width + j],
						sf::Vector2f(j, i), tileCounter, 0x09);
					break;
				default:
					layeredTile->layerTwo = new Tile(components._layerTwo[i * components._width + j],
						sf::Vector2f(j, i), tileCounter);
					break;
				}
			}
			else layeredTile->layerTwo = new Tile();

			if (components._layerThree[0] != -2)
				layeredTile->layerThree = new Tile(components._layerThree[i * components._width + j],
					sf::Vector2f(j, i), tileCounter);

			else layeredTile->layerThree = new Tile();

			if (components._layerSix[0] != -2)
				layeredTile->layerSix = new Tile(components._layerSix[i * components._width + j],
					sf::Vector2f(j, i), tileCounter);

			else layeredTile->layerSix = new Tile();

			if (components._canopyLayer[0] != -2) {
				switch (components._canopyLayer[i * components._width + j]) {
				case 52:
				case 53:
				case 54:
					layeredTile->canopy = new Tile(components._canopyLayer[i * components._width + j],
						sf::Vector2f(j, i), tileCounter, 0x10);
					break;
				default:
					layeredTile->canopy = new Tile(components._canopyLayer[i * components._width + j],
						sf::Vector2f(j, i), tileCounter);
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

	Map* retMap = _currMap;
	_currMap = nullptr;
	return retMap;
}
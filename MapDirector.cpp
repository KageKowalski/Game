#include "MapDirector.h"

MapDirector::MapDirector() {
	_currMap = nullptr;
}

MapDirector::~MapDirector() {
	unloadMap();
}

bool MapDirector::loadMap(unsigned int ID) {
	if (_currMap != nullptr)
		return false;

	const MapBuilder::Componets& components = MapBank::get().getMapComponents(ID);

	if (!_mapBuilder.build(components))
		return false;

	_currMap = _mapBuilder.produce();

	_currTextures.push_back(_currMap->getTileSet());
	_currTextures.push_back(_currMap->getUniversalSpriteSheet());
	_currTextures.push_back(_currMap->getLocalSpriteSheet());

	return true;
}

void MapDirector::unloadMap() {
	if (_currMap != nullptr) {
		delete _currMap;

		_currTextures.clear();
		_currVerticies.clear();
	}
}

void MapDirector::update() {
	if (_currMap != nullptr) {
		_currMap->update();

		_currVerticies.clear();

		_currVerticies.push_back(_currMap->getGroundVertices());
		_currVerticies.push_back(_currMap->getLayerTwoVertices());
		_currVerticies.push_back(_currMap->getLayerThreeVertices());
		_currVerticies.push_back(_currMap->getLocalSpriteVerticies());
		_currVerticies.push_back(_currMap->getUniversalSpriteVerticies());
		_currVerticies.push_back(_currMap->getLayerSixVertices());
		_currVerticies.push_back(_currMap->getCanopyVertices());
	}
}

const sf::Transform& MapDirector::getCurrTransform() const {
	return MapBank::get().getTransform();
}

const std::vector<sf::VertexArray>& MapDirector::getCurrVerticies() const {
	return _currVerticies;
}

const std::vector<sf::Texture>& MapDirector::getCurrTextures() const {
	return _currTextures;
}
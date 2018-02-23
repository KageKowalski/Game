// Klayton Kowalski

#include "TileSet.h"

TileSet::TileSet() {
	m_Width = 0;
	m_Height = 0;
}

TileSet::~TileSet() {}

bool TileSet::load(std::string tilesetFileName) {
	std::string filePath = tilesetFileName;

	if (!m_TileSet.loadFromFile(filePath)) return false;
	m_Width = m_TileSet.getSize().x;
	m_Height = m_TileSet.getSize().y;

	return true;
}

const sf::Texture& TileSet::getTexture() const {
	return m_TileSet;
}

unsigned int TileSet::getWidth() const {
	return m_Width;
}

unsigned int TileSet::getHeight() const {
	return m_Height;
}
// Klayton Kowalski

#ifndef TILESET_H
#define TILESET_H

#include <SFML/Graphics.hpp>

class TileSet {
	
public:

	TileSet();
	~TileSet();

	bool load(std::string tilesetFileName);

	const sf::Texture& getTexture() const;
	unsigned int getWidth() const;
	unsigned int getHeight() const;

private:

	sf::Texture m_TileSet;

	// Width of the tileset in tile units
	unsigned int m_Width;
	// Height of the tileset in tile units
	unsigned int m_Height;

};

#endif
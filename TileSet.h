// Klayton Kowalski

#ifndef TILESET_H
#define TILESET_H

#include <SFML/Graphics.hpp>

// Wrapper class for a texture of 16 x 16 tiles.
// Tile maps should use this instead of creating and loading their own tileset images.
class TileSet {
	
public:

	// Constructor simply init values; it does NOT load the tileset image.
	// To populate this tileset, call load().
	TileSet();
	~TileSet();

	// Loads the tileset image data into the application.
	// Pass in the tileset image's file name, including its file extension.
	// Returns false if attempt to access and load image data fails.
	bool load(std::string tilesetFileName);

	// Retrieves the texture.
	const sf::Texture& getTexture() const;

	// Retrieves the width of the tileset image.
	unsigned int getWidth() const;

	// Retrieves the height of the tileset image.
	unsigned int getHeight() const;

private:

	// The tileset image itself.
	sf::Texture m_TileSet;

	// Width of the tileset in tile units
	unsigned int m_Width;

	// Height of the tileset in tile units
	unsigned int m_Height;

};

#endif
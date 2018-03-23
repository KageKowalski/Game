// Klayton Kowalski

#ifndef RENDERER_H
#define RENDERER_H

#include "SFML/Graphics.hpp"

// THIS CLASS WORKS WITH LAYERS IN ORDER TO ACHIEVE A PROPER DRAWING ORDER.
// Layer levels are as follows:
// Layer 0 == Background
// Layer 1 == Ground tiles
// Layer 2 == Tiles overlapping ground tiles
// Layer 3 == Tiles overlapping layer 2 tiles
// Layer 4 == Sprites from the universal sprite sheet
// Layer 5 == Sprites from local sprite sheet
// Layer 6 == Tiles overlapping sprites
// Layer 7 == Canopy tiles
// Layer 8 == GUI components

// Example of each layer:
// Layer 0 == Background image of battle scene in Pokemon games
// Layer 1 == Plain grass tile
// Layer 2 == Flower tile
// Layer 3 == Fence tile
// Layer 4 == Player's sprite
// Layer 5 == Enemy's sprite local to "the grasslands"
// Layer 6 == Roof tile
// Layer 7 == Canopy of tree tile
// Layer 8 == Settings menu

// Holds the current state of every drawable object in the game.
// Renderer draws each of its components once per frame, drawing the entirety of the
// game's graphical components.
class Renderer : public sf::Drawable {

public:

	// Constructor sets up vertex meta information.
	Renderer();
	virtual ~Renderer();

	// Use this to "upload" an object's verticies to the renderer whenever there has been
	// a change in the object's vertex array. For example, if a sprite suddenly undergoes
	// a change in position, pass in its new vertex array.
	// Pass in the object's z-value, or layer level.
	void updateVerticies(const sf::VertexArray& verticies, int z);

	// Use this to "upload" an object's transform to the renderer whenever there has been
	// a change in the object's transform (overarching position, scale, or rotation).
	// For example, if we need to rotate the entire tilemap and all of its contents,
	// pass in its new transform after every rotation step.
	// Pass in the object's z-value, or layer level.
	void updateTransform(const sf::Transform& transform, int z);

	// Use this to "upload" an object's texture to the renderer whenever there has been
	// a change in the object's texture. For example, if transitioning from one area of
	// the world to a different area, and the tileset needs to be updated to reflect the
	// change in the look of tiles, pass in its new texture after it has been loaded.
	// Pass in the object's z-value, or layer level.
	void updateTexture(const sf::Texture& texture, int z);

	// Reset all verticies and nullify all textures at every layer.
	void clear();

private:

	// Draws all verticies onto the render window.
	// Pass in the render window to draw to and the Renderer class will take care of the render
	// states according to the transforms that are stored in renderer.
	void draw(sf::RenderTarget& target, sf::RenderStates) const override;

private:

	// Verticies ordered by layer level (least to greatest).
	// Each vertex array accounts for a single layer.
	sf::VertexArray m_Background;
	sf::VertexArray m_Ground;
	sf::VertexArray m_Z2;
	sf::VertexArray m_Z3;
	sf::VertexArray m_UniversalSprites;
	sf::VertexArray m_LocalSprites;
	sf::VertexArray m_Z6;
	sf::VertexArray m_Canopy;
	sf::VertexArray m_GUI;

	// Transforms ordered by layer level (least to greatest).
	// MapTransform accounts for layers 1 - 7.
	sf::Transform m_BackgroundTransform;
	sf::Transform m_MapTransform;
	sf::Transform m_GUITransform;
	
	// Textures ordered by layer level (least to greatest).
	// Tileset accounts for all tile-related layers (1 - 3, 6 - 7).
	const sf::Texture* m_BackgroundTexture;
	const sf::Texture* m_Tileset;
	const sf::Texture* m_UniversalSpriteSheet;
	const sf::Texture* m_LocalSpriteSheet;
	const sf::Texture* m_GUITexture;

};

#endif

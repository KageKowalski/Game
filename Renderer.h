// Klayton Kowalski

#ifndef RENDERER_H
#define RENDERER_H

#include "SFML/Graphics.hpp"

class Renderer : public sf::Drawable {

public:

	Renderer();
	virtual ~Renderer();

	void updateVerticies(const sf::VertexArray& verticies, int z);
	void updateTransform(const sf::Transform& transform, int z);
	void updateTexture(const sf::Texture& texture, int z);

	void clear();

private:

	void draw(sf::RenderTarget& target, sf::RenderStates) const override;

private:

	sf::VertexArray m_Background;
	sf::VertexArray m_Ground;
	sf::VertexArray m_Z2;
	sf::VertexArray m_Z3;
	sf::VertexArray m_UniversalSprites;
	sf::VertexArray m_LocalSprites;
	sf::VertexArray m_Z6;
	sf::VertexArray m_Canopy;
	sf::VertexArray m_GUI;

	sf::Transform m_BackgroundTransform;
	sf::Transform m_MapTransform;
	sf::Transform m_GUITransform;

	const sf::Texture* m_BackgroundTexture;
	const sf::Texture* m_Tileset;
	const sf::Texture* m_UniversalSpriteSheet;
	const sf::Texture* m_LocalSpriteSheet;
	const sf::Texture* m_GUITexture;

};

#endif
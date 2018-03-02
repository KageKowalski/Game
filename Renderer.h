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
	void updateTexture(sf::Texture& texture, int z);

	void clear();

private:

	void draw(sf::RenderTarget& target, sf::RenderStates) const override;

private:

	sf::VertexArray m_Background;
	sf::Transform m_BackgroundTransform;
	sf::Texture* m_BackgroundTexture;

	sf::VertexArray m_Ground;
	sf::Transform m_GroundTransform;
	sf::Texture* m_Tileset;

	sf::VertexArray m_Z2;
	sf::Transform m_Z2Transform;

	sf::VertexArray m_Z3;
	sf::Transform m_Z3Transform;

	sf::VertexArray m_UniversalSprites;
	sf::Transform m_SpritesTransform;
	sf::Texture* m_UniversalSpriteSheet;

	sf::VertexArray m_LocalSprites;
	sf::Texture* m_LocalSpriteSheet;

	sf::VertexArray m_Z6;
	sf::Transform m_Z6Transform;

	sf::VertexArray m_GUI;
	sf::Transform m_GUITransform;
	sf::Texture* m_GUITexture;

};

#endif
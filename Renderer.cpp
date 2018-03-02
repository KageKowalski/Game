// Klayton Kowalski

#include "Renderer.h"

Renderer::Renderer() {
	m_Background.setPrimitiveType(sf::PrimitiveType::Quads);
	m_Ground.setPrimitiveType(sf::PrimitiveType::Quads);
	m_Z2.setPrimitiveType(sf::PrimitiveType::Quads);
	m_Z3.setPrimitiveType(sf::PrimitiveType::Quads);
	m_UniversalSprites.setPrimitiveType(sf::PrimitiveType::Quads);
	m_LocalSprites.setPrimitiveType(sf::PrimitiveType::Quads);
	m_Z6.setPrimitiveType(sf::PrimitiveType::Quads);
	m_GUI.setPrimitiveType(sf::PrimitiveType::Quads);
	clear();
}

Renderer::~Renderer() {}

void Renderer::updateVerticies(const sf::VertexArray& verticies, int z) {
	size_t vertexCount = verticies.getVertexCount();
	switch (z) {
	case 0:
		if (m_Background.getVertexCount() != vertexCount) m_Background.resize(vertexCount);
		m_Background = verticies;
		break;
	case 1:
		if (m_Ground.getVertexCount() != vertexCount) m_Ground.resize(vertexCount);
		m_Ground = verticies;
		break;
	case 2:
		if (m_Z2.getVertexCount() != vertexCount) m_Z2.resize(vertexCount);
		m_Z2 = verticies;
		break;
	case 3:
		if (m_Z3.getVertexCount() != vertexCount) m_Z3.resize(vertexCount);
		m_Z3 = verticies;
		break;
	case 4:
		if (m_UniversalSprites.getVertexCount() != vertexCount) m_UniversalSprites.resize(vertexCount);
		m_UniversalSprites = verticies;
		break;
	case 5:
		if (m_LocalSprites.getVertexCount() != vertexCount) m_LocalSprites.resize(vertexCount);
		m_LocalSprites = verticies;
		break;
	case 6:
		if (m_Z6.getVertexCount() != vertexCount) m_Z6.resize(vertexCount);
		m_Z6 = verticies;
		break;
	case 7:
		if (m_GUI.getVertexCount() != vertexCount) m_GUI.resize(vertexCount);
		m_GUI = verticies;
		break;
	}
}

void Renderer::updateTransform(const sf::Transform& transform, int z) {
	switch (z) {
	case 0:
		m_BackgroundTransform = transform;
		break;
	case 1:
		m_GroundTransform = transform;
		break;
	case 2:
		m_Z2Transform = transform;
		break;
	case 3:
		m_Z3Transform = transform;
		break;
	case 4:
	case 5:
		m_SpritesTransform = transform;
		break;
	case 6:
		m_Z6Transform = transform;
		break;
	case 7:
		m_GUITransform = transform;
		break;
	}
}

void Renderer::updateTexture(const sf::Texture& texture, int z) {
	switch (z) {
	case 0:
		m_BackgroundTexture = &texture;
		break;
	case 1:
	case 2:
	case 3:
	case 6:
		m_Tileset = &texture;
		break;
	case 4:
		m_UniversalSpriteSheet = &texture;
		break;
	case 5:
		m_LocalSpriteSheet = &texture;
		break;
	case 7:
		m_GUITexture = &texture;
		break;
	}
}

void Renderer::draw(sf::RenderTarget& target, sf::RenderStates) const {
	if (m_BackgroundTexture != nullptr) {
		sf::RenderStates backgroundStates;
		backgroundStates.transform *= m_BackgroundTransform;
		backgroundStates.texture = m_BackgroundTexture;
		target.draw(m_Background, backgroundStates);
	}
	if (m_Tileset != nullptr) {
		sf::RenderStates groundStates;
		groundStates.transform *= m_GroundTransform;
		groundStates.texture = m_Tileset;
		target.draw(m_Ground, groundStates);

		sf::RenderStates Z2States;
		Z2States.transform *= m_Z2Transform;
		Z2States.texture = m_Tileset;
		target.draw(m_Z2, Z2States);

		sf::RenderStates Z3States;
		Z3States.transform *= m_Z3Transform;
		Z3States.texture = m_Tileset;
		target.draw(m_Z3, Z3States);
	}
	if (m_UniversalSpriteSheet != nullptr || m_LocalSpriteSheet != nullptr) {
		sf::RenderStates spritesStates;
		spritesStates.transform *= m_SpritesTransform;
		spritesStates.texture = m_UniversalSpriteSheet;
		target.draw(m_UniversalSprites, spritesStates);

		spritesStates.texture = m_LocalSpriteSheet;
		target.draw(m_LocalSprites, spritesStates);
	}
	if (m_Tileset != nullptr) {
		sf::RenderStates Z6States;
		Z6States.transform *= m_Z6Transform;
		Z6States.texture = m_Tileset;
		target.draw(m_Z6, Z6States);
	}
	if (m_GUITexture != nullptr) {
		sf::RenderStates GUIStates;
		GUIStates.transform *= m_GUITransform;
		GUIStates.texture = m_GUITexture;
		target.draw(m_GUI, GUIStates);
	}
}

void Renderer::clear() {
	m_Background.clear();
	m_BackgroundTexture = nullptr;
	
	m_Ground.clear();
	m_Tileset = nullptr;

	m_Z2.clear();

	m_Z3.clear();

	m_UniversalSprites.clear();
	m_UniversalSpriteSheet = nullptr;

	m_LocalSprites.clear();
	m_LocalSpriteSheet = nullptr;

	m_Z6.clear();

	m_GUI.clear();
	m_GUITexture = nullptr;
}
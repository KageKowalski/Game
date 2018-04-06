#include "FullLoading.h"

FullLoading::FullLoading() {
	m_Verticies.setPrimitiveType(sf::PrimitiveType::Quads);
	m_Verticies.resize(4);
}

FullLoading::~FullLoading() {}

bool FullLoading::load(const std::string& backgroundFileName) {
	const std::string filePath = backgroundFileName;

	if (!m_Texture.loadFromFile(filePath)) return false;

	vertexFill();

	return true;
}

const sf::Texture& FullLoading::getTexture() const {
	return m_Texture;
}

const sf::VertexArray& FullLoading::getVerticies() const {
	return m_Verticies;
}

void FullLoading::vertexFill() {
	sf::Vector2u size = m_Texture.getSize();

	sf::Vertex* quad = &m_Verticies[0];

	quad->position = sf::Vector2f(0.0f, 0.0f);
	quad->texCoords = sf::Vector2f(0.0f, 0.0f);

	quad++;
	quad->position = sf::Vector2f(800.0f, 0.0f);
	quad->texCoords = sf::Vector2f(size.x, 0.0f);

	quad++;
	quad->position = sf::Vector2f(800.0f, 600.0f);
	quad->texCoords = sf::Vector2f(size.x, size.y);

	quad++;
	quad->position = sf::Vector2f(0.0f, 600.0f);
	quad->texCoords = sf::Vector2f(0.0f, size.y);
}
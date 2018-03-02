// Klayton Kowalski

#include "SpriteMap.h"

SpriteMap::SpriteMap(const sf::Vector2f& scale) {
	m_UniversalSpriteVerticies.setPrimitiveType(sf::PrimitiveType::Quads);
	m_LocalSpriteVerticies.setPrimitiveType(sf::PrimitiveType::Quads);
	setScale(scale);
}

SpriteMap::~SpriteMap() {}

bool SpriteMap::build(const std::string& universalSpriteSheetFileName, const std::string& localSpriteSheetFileName,
	const std::vector<Character*>& characters)
{
	std::string universalSpriteSheetFilePath = universalSpriteSheetFileName;
	std::string localSpriteSheetFilePath = localSpriteSheetFileName;

	if (!m_UniversalSpriteSheet.loadFromFile(universalSpriteSheetFilePath) ||
		!m_LocalSpriteSheet.loadFromFile(localSpriteSheetFilePath))
		return false;

	m_Characters = characters;

	size_t universalCount = 0;
	size_t localCount = 0;
	for (const Character* const character : m_Characters) {
		if (character->isUniversal()) universalCount++;
		if (character->isUniversal()) localCount++;
	}

	m_UniversalSpriteVerticies.resize(universalCount * 4);
	m_LocalSpriteVerticies.resize(localCount * 4);

	for (size_t i = 0; i < m_Characters.size(); i++)
		vertexFill(m_Characters.at(i), i * 4);

	return true;
}

void SpriteMap::vertexFill(const Character* const character, size_t offset) {
	float i = character->getPosition().y;
	float j = character->getPosition().x;
	unsigned int width = character->getFrameWidth();
	unsigned int height = character->getFrameHeight();
	sf::Vector2f texCoords = character->getTextureCoords();
	bool universal = character->isUniversal();

	sf::Vertex* quad = universal ? &m_UniversalSpriteVerticies[offset] : &m_LocalSpriteVerticies[offset];

	quad->position = sf::Vector2f(j, i);
	quad->texCoords = texCoords;

	quad++;
	quad->position = sf::Vector2f(j + width, i);
	quad->texCoords = sf::Vector2f(texCoords.x + width, texCoords.y);

	quad++;
	quad->position = sf::Vector2f(j + width, i + height);
	quad->texCoords = sf::Vector2f(texCoords.x + width, texCoords.y + height);

	quad++;
	quad->position = sf::Vector2f(j, i + height);
	quad->texCoords = sf::Vector2f(texCoords.x, texCoords.y + height);
}
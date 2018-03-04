// Klayton Kowalski

#include "SpriteMap.h"

SpriteMap::SpriteMap() {
	m_UniversalSpriteVerticies.setPrimitiveType(sf::PrimitiveType::Quads);
	m_LocalSpriteVerticies.setPrimitiveType(sf::PrimitiveType::Quads);
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

void SpriteMap::update(sf::Time deltaTime) {
	m_Characters.at(0)->update(deltaTime);
	vertexFill(m_Characters.at(0), 0);
}

const sf::Texture& SpriteMap::getUniversalSpriteSheet() const {
	return m_UniversalSpriteSheet;
}

const sf::Texture& SpriteMap::getLocalSpriteSheet() const {
	return m_LocalSpriteSheet;
}

const sf::VertexArray& SpriteMap::getUniversalSpriteVerticies() const {
	return m_UniversalSpriteVerticies;
}

const sf::VertexArray& SpriteMap::getLocalSpriteVerticies() const {
	return m_LocalSpriteVerticies;
}

Character* SpriteMap::getPlayer() {
	return m_Characters.at(0);
}

void SpriteMap::vertexFill(const Character* const character, size_t offset) {
	float i = character->getPosition().y;
	float j = character->getPosition().x;
	unsigned int width = character->getFrameWidth();
	unsigned int height = character->getFrameHeight();
	sf::Vector2f texCoords = character->getTextureCoords();
	unsigned int animStep = character->getCurrAnimStep();

	sf::Vertex* quad = character->isUniversal() ? &m_UniversalSpriteVerticies[offset] : &m_LocalSpriteVerticies[offset];

	quad->position = sf::Vector2f(j, i);
	quad->texCoords = sf::Vector2f(texCoords.x, texCoords.y + (animStep * height));

	quad++;
	quad->position = sf::Vector2f(j + width, i);
	quad->texCoords = sf::Vector2f(texCoords.x + width, texCoords.y + (animStep * height));

	quad++;
	quad->position = sf::Vector2f(j + width, i + height);
	quad->texCoords = sf::Vector2f(texCoords.x + width, texCoords.y + height + (animStep * height));

	quad++;
	quad->position = sf::Vector2f(j, i + height);
	quad->texCoords = sf::Vector2f(texCoords.x, texCoords.y + height + (animStep * height));
}
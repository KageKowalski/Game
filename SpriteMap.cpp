// Klayton Kowalski

#include "SpriteMap.h"

SpriteMap::SpriteMap() {
	m_UniversalSpriteVerticies.setPrimitiveType(sf::PrimitiveType::Quads);
	m_LocalSpriteVerticies.setPrimitiveType(sf::PrimitiveType::Quads);

	EventBus::get().registerListener(Event::EventType::EV_RUNDOWN, this);
	EventBus::get().registerListener(Event::EventType::EV_RUNUP, this);
	EventBus::get().registerListener(Event::EventType::EV_RUNLEFT, this);
	EventBus::get().registerListener(Event::EventType::EV_RUNRIGHT, this);
	EventBus::get().registerListener(Event::EventType::EV_WALKDOWN, this);
	EventBus::get().registerListener(Event::EventType::EV_WALKUP, this);
	EventBus::get().registerListener(Event::EventType::EV_WALKLEFT, this);
	EventBus::get().registerListener(Event::EventType::EV_WALKRIGHT, this);
}

SpriteMap::~SpriteMap() {
	EventBus::get().removeListener(Event::EventType::EV_RUNDOWN, this);
	EventBus::get().removeListener(Event::EventType::EV_RUNUP, this);
	EventBus::get().removeListener(Event::EventType::EV_RUNLEFT, this);
	EventBus::get().removeListener(Event::EventType::EV_RUNRIGHT, this);
	EventBus::get().removeListener(Event::EventType::EV_WALKDOWN, this);
	EventBus::get().removeListener(Event::EventType::EV_WALKUP, this);
	EventBus::get().removeListener(Event::EventType::EV_WALKLEFT, this);
	EventBus::get().removeListener(Event::EventType::EV_WALKRIGHT, this);
}

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
	for (size_t i = 0; i < m_Characters.size(); i++) {
		m_Characters.at(i)->update(deltaTime);
		vertexFill(m_Characters.at(i), i * 4);
	}
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

const std::vector<Character*>& SpriteMap::getCharacters() const {
	return m_Characters;
}

std::vector<Character*> SpriteMap::getReachableCharacters() const {
	std::vector<Character*> reachables;

	Player const * const player = &Player::get();

	for (Character* character : m_Characters)
		if (sqrt(pow(character->getCenterPosition().x - player->getCenterPosition().x, 2)
			+ pow(character->getCenterPosition().y - player->getCenterPosition().y, 2)) <= 24.0f
			&& character != &Player::get())
			reachables.push_back(character);

	return reachables;
}

bool SpriteMap::isTouching(Character const * const curr, Direction facing) const {
	for (Character* character : m_Characters)
		if (sqrt(pow(curr->getCenterPosition().x - character->getCenterPosition().x, 2)
			+ pow(curr->getCenterPosition().y - character->getCenterPosition().y, 2)) <= 16.0f
			&& curr != character)
			return true;

	return false;
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

void SpriteMap::handleEvent(Event* const e) {
	switch (e->getType()) {
		
	}
}
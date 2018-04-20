// Klayton Kowalski

#ifndef SPRITEMAP_H
#define SPRITEMAP_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "Character.h"
#include "Player.h"

class SpriteMap : EventListener {

public:

	SpriteMap();
	virtual ~SpriteMap();

	bool build(const std::string& universalSpriteSheetFileName, const std::string& localSpriteSheetFileName,
		const std::vector<Character*>& characters);

	void update(sf::Time deltaTime);

	const sf::Texture& getUniversalSpriteSheet() const;
	const sf::Texture& getLocalSpriteSheet() const;
	const sf::VertexArray& getUniversalSpriteVerticies() const;
	const sf::VertexArray& getLocalSpriteVerticies() const;
	const std::vector<Character*>& getCharacters() const;

	std::vector<Character*> getReachableCharacters() const;
	bool isTouching(Character const * const curr, Direction facing) const;

private:

	void vertexFill(const Character* const character, size_t offset);

	void handleEvent(Event* const e) override;

private:

	sf::Texture m_UniversalSpriteSheet;
	sf::Texture m_LocalSpriteSheet;

	sf::VertexArray m_UniversalSpriteVerticies;
	sf::VertexArray m_LocalSpriteVerticies;

	std::vector<Character*> m_Characters;

};

#endif
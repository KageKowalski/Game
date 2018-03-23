// Klayton Kowalski

#ifndef SPRITEMAP_H
#define SPRITEMAP_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "Character.h"

class SpriteMap {

public:

	SpriteMap();
	~SpriteMap();

	bool build(const std::string& universalSpriteSheetFileName, const std::string& localSpriteSheetFileName,
		const std::vector<Character*>& characters);

	void update(sf::Time deltaTime);

	const sf::Texture& getUniversalSpriteSheet() const;
	const sf::Texture& getLocalSpriteSheet() const;
	const sf::VertexArray& getUniversalSpriteVerticies() const;
	const sf::VertexArray& getLocalSpriteVerticies() const;
	const std::vector<Character*>& getCharacters() const;

	Character* getPlayer() const;
	std::vector<Character*> getReachableCharacters() const;
	bool isTouching(Character const * const curr, Direction facing) const;

private:

	void vertexFill(const Character* const character, size_t offset);

private:

	sf::Texture m_UniversalSpriteSheet;
	sf::Texture m_LocalSpriteSheet;

	sf::VertexArray m_UniversalSpriteVerticies;
	sf::VertexArray m_LocalSpriteVerticies;

	std::vector<Character*> m_Characters;

};

#endif
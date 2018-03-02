// Klayton Kowalski

#ifndef SPRITEMAP_H
#define SPRITEMAP_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "Character.h"

class SpriteMap : public sf::Transformable {

public:

	SpriteMap(const sf::Vector2f& scale);
	~SpriteMap();

	bool build(const std::string& universalSpriteSheetFileName, const std::string& localSpriteSheetFileName,
		const std::vector<Character*>& characters);

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
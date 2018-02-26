#ifndef SPRITEMAP_H
#define SPRITEMAP_H

#include <SFML/Graphics.hpp>

class SpriteMap : public sf::Drawable, public sf::Transformable {

public:

	SpriteMap();
	virtual ~SpriteMap();

private:

	sf::VertexArray m_Verticies;

};

#endif
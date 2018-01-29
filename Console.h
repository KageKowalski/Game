#ifndef CONSOLE_H
#define CONSOLE_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "Output.h"

class Console : public sf::Drawable {

public:

	Console();
	virtual ~Console();

private:

	// Draws loaded output onto the screen
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:

	// Verticies to be drawn onto screen
	sf::VertexArray m_Verticies;

	// All output to be drawn onto screen
	std::vector<Output*> m_Output;

};

#endif
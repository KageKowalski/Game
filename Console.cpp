#include "Console.h"

Console::Console() {}

Console::~Console() {}

void Console::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_Verticies, states);
}
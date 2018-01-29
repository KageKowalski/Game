#ifndef OUTPUT_H
#define OUTPUT_H

#include <SFML/Graphics.hpp>

#include <vector>

class Output : public sf::Transformable {

public:

	Output();
	~Output();

private:

	sf::Text m_Text;

};

#endif
// Klayton Kowalski

#ifndef TEXTBANK_H
#define TEXTBANK_H

#include <SFML/Graphics.hpp>
#include <map>

class TextBank {

public:

	TextBank();

	TextBank(const TextBank&) = delete;
	void operator=(const TextBank&) = delete;

	static TextBank& get() {
		static TextBank instance;
		return instance;
	}

	~TextBank();

public:

	bool init();

	const sf::Text& getText(size_t index) const;

private:

	sf::Text m_TextBank[1];
	sf::Font m_FontDependencies[1];

};

#endif

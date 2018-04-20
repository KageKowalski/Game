// Klayton Kowalski

#include "TextBank.h"

TextBank::TextBank() {}

TextBank::~TextBank() {}

bool TextBank::init() {
	const std::string filePath = "sansation.ttf";

	if (!m_FontDependencies[0].loadFromFile(filePath))
		return false;

	m_TextBank[0].setString(sf::String("--> Klayton's First Test String <--"));
	m_TextBank[0].setFont(m_FontDependencies[0]);
	m_TextBank[0].setFillColor(sf::Color::White);

	return true;
}

const sf::Text& TextBank::getText(size_t index) const {
	return m_TextBank[index];
}
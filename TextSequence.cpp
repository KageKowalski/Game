#include "TextSequence.h"

TextSequence::TextSequence() : m_Index(0) {}

TextSequence::~TextSequence() {}

void TextSequence::update(sf::Time deltaTime) {
	m_ElapsedTime += deltaTime;
}

void TextSequence::draw(sf::RenderWindow& window) {
	window.draw(m_CurrOutput);
}

void TextSequence::appendInstruction(Instruction instruction) {
	m_Instructions.push_back(instruction);
}
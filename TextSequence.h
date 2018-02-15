#ifndef TEXTSEQUENCE_H
#define TEXTSEQUENCE_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "Instruction.h"

class TextSequence {

public:

	TextSequence();
	~TextSequence();

	// Updates the sequence
	void update(sf::Time deltaTime);

	// Draws the current state of the sequence
	void draw(sf::RenderWindow& window);

	// Appends an instruction to the sequence
	void appendInstruction(Instruction instruction);

private:

	// Text that will scroll throughout the cutscene
	std::vector<sf::Text> m_TextBank;

	// Current text to render
	size_t m_Index;

	// Time elapsed since last measuring milestone
	sf::Time m_ElapsedTime;

	// Current text being built and drawn onto the screen
	sf::Text m_CurrOutput;

	// Sequence instructions
	std::vector<Instruction> m_Instructions;

};

#endif
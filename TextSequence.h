#ifndef TEXTSEQUENCE_H
#define TEXTSEQUENCE_H

#include <SFML/Graphics.hpp>
#include <vector>

class TextSequence {

	// Instance of text that rolls in the cutscene along with its properties
	struct Instance {

		// String to display
		sf::Text m_Text;

		// Delay between individual character outputs
		sf::Time m_CharacterDelay;

		Instance(const sf::Text& text, sf::Time characterDelay);

	};

public:

	TextSequence();
	TextSequence(sf::Time instanceDelay);
	~TextSequence();

	// Appends another instance of text to the end of the cutscene
	void appendInstance(const Instance& instance);

	// Updates the sequence
	void update(sf::Time deltaTime);

	// Draws the current state of the sequence
	void draw(sf::RenderWindow& window);

private:

	// Instances of text will roll throughout the cutscene
	std::vector<Instance> m_Instances;

	// Delay between text outputs
	sf::Time m_InstanceDelay;

	// Current instance to render in vector
	size_t m_Index;

	// Time elapsed since last measuring milestone (character delay, instance delay, etc)
	sf::Time m_ElapsedTime;

	// Current text being built and drawn onto the screen
	sf::Text m_CurrOutput;

	// Waiting for the next instance to begin rendering
	bool m_WaitInstance;

	// Waiting for the next character to begin rendering within current instance
	bool m_WaitCharacter;

};

#endif
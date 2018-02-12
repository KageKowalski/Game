#include "TextSequence.h"

TextSequence::TextSequence() {
	m_Index = 0;
	m_WaitInstance = true;
	m_WaitCharacter = false;
}

TextSequence::TextSequence(sf::Time instanceDelay) {
	m_InstanceDelay = instanceDelay;
	m_Index = 0;
	m_WaitInstance = true;
	m_WaitCharacter = false;
}

TextSequence::~TextSequence() {}

void TextSequence::appendInstance(const sf::Text& text, sf::Time characterDelay) {
	Instance instance(text, characterDelay);
	m_Instances.push_back(instance);
}

TextSequence::Instance::Instance(const sf::Text& text, sf::Time characterDelay) {
	m_Text = text;
	m_CharacterDelay = characterDelay;
}

void TextSequence::update(sf::Time deltaTime) {
	m_CurrOutput = m_Instances.at(m_Index).m_Text;
	return;

	// Abort if text sequence is empty
	if (m_Instances.size() == 0) return;

	// Add time since last frame
	m_ElapsedTime += deltaTime;

	// Cache data
	const Instance& currInstance = m_Instances.at(m_Index);

	// If we're waiting for the next character to be drawn
	if (m_WaitCharacter) {
		// If it's time for the next character to be drawn
		if (m_ElapsedTime >= currInstance.m_CharacterDelay) {
			m_ElapsedTime = sf::Time::Zero;

			// Add next letter of instance
			m_CurrOutput.setString(m_CurrOutput.getString()
				+ currInstance.m_Text.getString().substring(m_CurrOutput.getString().getSize(), 1));
		}
	}
	// Else if we're waiting for the next instance to start being drawn
	else if (m_WaitInstance) {
		// If it's time for the next instance to start being drawn
		if (m_ElapsedTime >= m_InstanceDelay) {
			m_ElapsedTime = sf::Time::Zero;

			// Enable characters to begin rendering
			m_WaitInstance = false;
			m_WaitCharacter = true;
		}
	}

	// If we've reached the end of the instance, begin working on transitioning to next instance
	if (m_CurrOutput.getString().getSize() == currInstance.m_Text.getString().getSize()) {
		m_WaitInstance = true;
		m_WaitCharacter = false;
		m_Index++;
		m_CurrOutput.setString(L"");
	}
}

void TextSequence::draw(sf::RenderWindow& window) {
	window.draw(m_CurrOutput);
}

void TextSequence::setInstanceDelay(sf::Time instanceDelay) {
	m_InstanceDelay = instanceDelay;
}
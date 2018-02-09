#include "TextSequence.h"

TextSequence::TextSequence() {
	m_InstanceDelay = sf::Time::Zero;
	m_Index = 0;
	m_ElapsedTime = sf::Time::Zero;
	m_WaitInstance = true;
	m_WaitCharacter = false;
}

TextSequence::TextSequence(sf::Time instanceDelay) {
	m_InstanceDelay = instanceDelay;
	m_Index = 0;
	m_ElapsedTime = sf::Time::Zero;
	m_WaitInstance = true;
	m_WaitCharacter = false;
}

TextSequence::~TextSequence() {}

void TextSequence::appendInstance(const Instance& instance) {
	m_Instances.push_back(instance);
}

TextSequence::Instance::Instance(const sf::Text& text, sf::Time characterDelay) {
	m_Text = text;
	m_CharacterDelay = characterDelay;
}

void TextSequence::update(sf::Time deltaTime) {
	// Add time since last frame
	m_ElapsedTime += deltaTime;

	sf::Time characterDelay = m_Instances.at(m_Index).m_CharacterDelay;
	sf::Time instanceDelay = m_InstanceDelay;

	// If line is being drawn, calc char delay
	// Once char delay is done, char++
	// If line is done being drawn, calc instance delay
	// Once instance delay complete, index++

	// If we're waiting for the next character to be drawn
	if (m_WaitCharacter) {
		if (m_ElapsedTime >= m_Instances.at(m_Index).m_CharacterDelay) {
			m_ElapsedTime = sf::Time::Zero;
		}
	}
	// Else if we're waiting for the next instance to start being drawn
	else if (m_WaitInstance) {

	}

}

void TextSequence::draw(sf::RenderWindow& window) {

}
#include "NPC.h"

NPC::NPC(const sf::Vector2f position, int initAnimStep, unsigned int totalAnimSteps, unsigned int frameWidth,
	unsigned int frameHeight, const sf::String& name)
	: Character(position, initAnimStep, totalAnimSteps, frameWidth, frameHeight, name)
{}

NPC::~NPC() {}
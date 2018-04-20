#ifndef FULLLOADING_H
#define FULLLOADING_H

#include <SFML/Graphics.hpp>
#include <string>

#include "Events.h"

class FullLoading : public EventListener {

public:

	FullLoading();
	virtual ~FullLoading();

	bool load(const std::string& backgroundFileName);

	const sf::Texture& getTexture() const;
	const sf::VertexArray& getVerticies() const;

private:

	void vertexFill();

	void handleEvent(Event* const e) override {}

private:

	sf::Texture m_Texture;
	sf::VertexArray m_Verticies;

};

#endif
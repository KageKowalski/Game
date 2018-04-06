#ifndef FULLLOADING_H
#define FULLLOADING_H

#include <SFML/Graphics.hpp>
#include <string>

class FullLoading {

public:

	FullLoading();
	~FullLoading();

	bool load(const std::string& backgroundFileName);

	const sf::Texture& getTexture() const;
	const sf::VertexArray& getVerticies() const;

private:

	void vertexFill();

private:

	sf::Texture m_Texture;
	sf::VertexArray m_Verticies;

};

#endif
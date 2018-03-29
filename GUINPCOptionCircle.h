#ifndef GUINPCOPTIONCIRCLE_H
#define GUINPCOPTIONCIRCLE_H

#include <SFML/System.hpp>
#include <string>

class GUINPCOptionCircle {

public:

	GUINPCOptionCircle();
	~GUINPCOptionCircle();

	bool load(const std::string& GUISheetFileName, const sf::Vector2f& NPCPosition);

private:



};

#endif
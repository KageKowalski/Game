#ifndef INPUT_H
#define INPUT_H

#include <SFML/Window.hpp>
#include "GameState.h"
#include "Events.h"
#include <memory>

class Input {

public:

	Input();
	~Input();

	void analyze(GameState state);

private:

	

};

#endif

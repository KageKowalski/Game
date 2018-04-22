#ifndef INPUT_H
#define INPUT_H

#include <SFML/Window.hpp>
#include "GameState.h"
#include "Events.h"
#include <memory>
#include "MapBank.h"

class Input {

public:

	Input();
	virtual ~Input();

	void analyze(GameState state);

};

#endif

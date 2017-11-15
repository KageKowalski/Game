#include "System.hpp"

#define PLAYER Player::get()

int main()
{
	System system;
	int retCode = system.run();
	system.shutDown();
	return retCode;
}

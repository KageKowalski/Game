#include "System.hpp"

int main()
{
	System system;
	int retCode = system.run();
	system.shutDown();
	return retCode;
}

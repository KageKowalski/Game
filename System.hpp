#ifndef _SYSTEM
#define _SYSTEM 1

#include <iostream>

#include "Player.hpp"

using namespace std;

class System {

public:
	int run();
	void shutDown();

private:
	void init();
	void printPlayerStats() const;

private:
	Player* player;

};

int System::run() {
	int retCode = 0;

	printPlayerStats();
	
	return retCode;
}

void System::init() {
	player = &Player::get();
}

void System::shutDown() {
	
}

void System::printPlayerStats() const {
	cout << "++++++++++ PLAYER STATS ++++++++++" << endl;
	cout << "HP   = " << player->getHp() << endl;
	cout << "STR  = " << player->getStr() << endl;
	cout << "DEF  = " << player->getDef() << endl;
	cout << "SPD  = " << player->getSpd() << endl;
	cout << "LCK  = " << player->getLck() << endl;
	cout << "PP   = " << player->getPp() << endl;
	cout << "EXP  = " << player->getExp() << endl;
	cout << "LVL  = " << player->getLevel() << endl;
	cout << "----------------------------------" << endl;
}

#endif
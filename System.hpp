#ifndef _SYSTEM
#define _SYSTEM 1

#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <string>

#include "Player.hpp"
#include "RoomSpecifiers.hpp"

using namespace std;

// ======================================================================================
// DEFINITIONS
// ======================================================================================

class System {

public:

	// Contains the game loop
	int run();

	// Frees resources
	void shutDown();

private:

	// Initializes game components on startup
	void init();

	// Prints player specs
	void playerSpecs() const;

	// Level up sequence
	void levelUp();

	// Draws the currently loaded room
	void drawRoom(const vector<RoomExit>& roomExits, const vector<RoomEntity>& roomEntities,
		const pair<int, int>& numEntities, RoomExit prevRoomDir) const;

private:

	// Player
	Player* player;

};

// ======================================================================================
// IMPLEMENTATIONS
// ======================================================================================

// Contains the game loop
int System::run() {
	int retCode = 0;

	init();

	vector<RoomExit> roomExits;
	roomExits.push_back(RoomExit::UP);
	roomExits.push_back(RoomExit::RIGHT);
	roomExits.push_back(RoomExit::DOWN);
	roomExits.push_back(RoomExit::LEFT);
	vector<RoomEntity> roomEntities;
	roomEntities.push_back(RoomEntity::INTERACTABLE);
	roomEntities.push_back(RoomEntity::MONSTER);
	drawRoom(roomExits, roomEntities, pair<int,int>(2, 6), RoomExit::UP);

	playerSpecs();
	
	return retCode;
}

// Initializes game components on startup
void System::init() {
	player = &Player::get();
}

// Frees resources
void System::shutDown() {
	this_thread::sleep_for(chrono::seconds(2));
}

// Prints player stats
void System::playerSpecs() const {
	cout << endl;
	cout << "++++++++++ PLAYER SPECS ++++++++++" << endl;
	this_thread::sleep_for(chrono::milliseconds(50));
	cout << "HEALTH          = " << player->getHp() << endl;
	this_thread::sleep_for(chrono::milliseconds(50));
	cout << "STRENGTH        = " << player->getStr() << endl;
	this_thread::sleep_for(chrono::milliseconds(50));
	cout << "DEFENSE         = " << player->getDef() << endl;
	this_thread::sleep_for(chrono::milliseconds(50));
	cout << "SPEED           = " << player->getSpd() << endl;
	this_thread::sleep_for(chrono::milliseconds(50));
	cout << "LUCK            = " << player->getLck() << endl;
	this_thread::sleep_for(chrono::milliseconds(50));
	cout << "STAMINA         = " << player->getPp() << endl;
	this_thread::sleep_for(chrono::milliseconds(50));
	cout << "CRIT CHANCE     = " << player->getCritPercent() << "%" << endl;
	this_thread::sleep_for(chrono::milliseconds(50));
	cout << "DODGE CHANCE    = " << player->getDodgePercent() << "%" << endl;
	this_thread::sleep_for(chrono::milliseconds(50));
	cout << "EXPERIENCE      = " << player->getExp() << endl;
	this_thread::sleep_for(chrono::milliseconds(50));
	cout << "LEVEL           = " << player->getLevel() << endl;
	this_thread::sleep_for(chrono::milliseconds(50));
	cout << "TO NEXT LEVEL   = " << player->nextLevel() << endl;
	this_thread::sleep_for(chrono::milliseconds(50));
	cout << "GOLD            = " << player->getGold() << endl;
	this_thread::sleep_for(chrono::milliseconds(50));
	cout << "----------------------------------" << endl;
}

// Level up sequence
void System::levelUp() {

}

// Draws the currently loaded room
void System::drawRoom(const vector<RoomExit>& roomExits, const vector<RoomEntity>& roomEntities,
	const pair<int, int>& numEntites, RoomExit prevRoomDir) const {
	const int ROOM_WIDTH = 18;
	const int ROOM_HEIGHT = 7;
	const int LEFT_MARGIN = 3;
	string output = "";
	output += "    ------------- ";
	output += "   |             |";
	output += "   |             |";
	output += "   |             |";
	output += "   |             |";
	output += "   |             |";
	output += "    ------------- ";

	// Edit room for correct exits
	for (RoomExit exitType : roomExits) {
		if (exitType == RoomExit::UP) {
			output.at(ROOM_WIDTH / 2 - 2 + LEFT_MARGIN / 2) = '#';
			output.at(ROOM_WIDTH / 2 - 1 + LEFT_MARGIN / 2) = ' ';
			output.at(ROOM_WIDTH / 2 + LEFT_MARGIN / 2) = ' ';
			output.at(ROOM_WIDTH / 2 + 1 + LEFT_MARGIN / 2) = ' ';
			output.at(ROOM_WIDTH / 2 + 2 + LEFT_MARGIN / 2) = '#';
		}
		else if (exitType == RoomExit::RIGHT) {
			output.at(ROOM_WIDTH * (ROOM_HEIGHT / 2) - 1) = '#';
			output.at(ROOM_WIDTH * (ROOM_HEIGHT / 2 + 1) - 1) = ' ';
			output.at(ROOM_WIDTH * (ROOM_HEIGHT / 2 + 2) - 1) = '#';
		}
		else if (exitType == RoomExit::DOWN) {
			output.at((ROOM_WIDTH / 2 - 2) + (ROOM_HEIGHT - 1) * ROOM_WIDTH + LEFT_MARGIN / 2) = '#';
			output.at((ROOM_WIDTH / 2 - 1) + (ROOM_HEIGHT - 1) * ROOM_WIDTH + LEFT_MARGIN / 2) = ' ';
			output.at((ROOM_WIDTH / 2) + (ROOM_HEIGHT - 1) * ROOM_WIDTH + LEFT_MARGIN / 2) = ' ';
			output.at((ROOM_WIDTH / 2 + 1) + (ROOM_HEIGHT - 1) * ROOM_WIDTH + LEFT_MARGIN / 2) = ' ';
			output.at((ROOM_WIDTH / 2 + 2) + (ROOM_HEIGHT - 1) * ROOM_WIDTH + LEFT_MARGIN / 2) = '#';
		}
		else if (exitType == RoomExit::LEFT) {
			output.at(ROOM_WIDTH * (ROOM_HEIGHT / 2 - 1) + LEFT_MARGIN) = '#';
			output.at(ROOM_WIDTH * (ROOM_HEIGHT / 2) + LEFT_MARGIN) = ' ';
			output.at(ROOM_WIDTH * (ROOM_HEIGHT / 2 + 1) + LEFT_MARGIN) = '#';
		}
	}
	
	// Edit room for correct entities and number of entities
	if (roomEntities.size() == 2) {
		output.at(ROOM_WIDTH * ROOM_HEIGHT / 2) = 'M';
		output.at(ROOM_WIDTH * ROOM_HEIGHT / 2 + ROOM_WIDTH) = numEntites.first + '0';
		output.at(ROOM_WIDTH * ROOM_HEIGHT / 2 + 2) = 'I';
		output.at(ROOM_WIDTH * ROOM_HEIGHT / 2 + 2 + ROOM_WIDTH) = numEntites.second + '0';
	}
	else if(roomEntities.size() == 1) {
		if (roomEntities.at(0) == RoomEntity::MONSTER) {
			output.at(ROOM_WIDTH * ROOM_HEIGHT / 2 + 1) = 'M';
			output.at(ROOM_WIDTH * ROOM_HEIGHT / 2 + 1 + ROOM_WIDTH) = numEntites.first + '0';
		}
		else {
			output.at(ROOM_WIDTH * ROOM_HEIGHT / 2 + 1) = 'I';
			output.at(ROOM_WIDTH * ROOM_HEIGHT / 2 + 1 + ROOM_WIDTH) = numEntites.second + '0';
		}
	}

	// Edit room for correct player placement
	if (prevRoomDir == RoomExit::UP) output.at(ROOM_WIDTH / 2 + LEFT_MARGIN / 2 + ROOM_WIDTH) = 'P';
	else if (prevRoomDir == RoomExit::RIGHT) output.at(ROOM_WIDTH * (ROOM_HEIGHT / 2 + 1) - 3) = 'P';
	else if (prevRoomDir == RoomExit::DOWN) output.at((ROOM_WIDTH / 2) + (ROOM_HEIGHT - 2) * ROOM_WIDTH + LEFT_MARGIN / 2) = 'P';
	else if (prevRoomDir == RoomExit::LEFT) output.at(ROOM_WIDTH * (ROOM_HEIGHT / 2) + LEFT_MARGIN + 2) = 'P';

	// Draw completed room
	cout << endl;
	for (int i = 0; i < ROOM_HEIGHT; i++) {
		cout << output.substr(ROOM_WIDTH * i, ROOM_WIDTH) << endl;
		this_thread::sleep_for(chrono::milliseconds(50));
	}
}

#endif

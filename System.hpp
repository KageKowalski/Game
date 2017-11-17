#ifndef _SYSTEM
#define _SYSTEM 1

#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <string>
#include <limits>

#include "Player.hpp"
#include "RoomSpecifiers.hpp"

using namespace std;

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

	// Trigger stat point distribution event
	void statPointDistribution(int points);

	// Level up sequence
	void levelUp(int points);

	// Draws the currently loaded room
	void drawRoom(const vector<RoomExit>& roomExits, const vector<RoomEntity>& roomEntities,
		const pair<int, int>& numEntities, RoomExit prevRoomDir) const;

private:

	// Player
	Player* player;

};

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

	levelUp(10);
	
	return retCode;
}

void System::init() {
	player = &Player::get();
}

void System::shutDown() {
	this_thread::sleep_for(chrono::seconds(3));
}

void System::playerSpecs() const {
	cout << endl;
	cout << "  ----- PLAYER SPECS -----" << endl;
	this_thread::sleep_for(chrono::milliseconds(50));
	cout << "  Health         = " << player->getHp() << endl;
	this_thread::sleep_for(chrono::milliseconds(50));
	cout << "  Strength        = " << player->getStr() << endl;
	this_thread::sleep_for(chrono::milliseconds(50));
	cout << "  Defense         = " << player->getDef() << endl;
	this_thread::sleep_for(chrono::milliseconds(50));
	cout << "  Speed           = " << player->getSpd() << endl;
	this_thread::sleep_for(chrono::milliseconds(50));
	cout << "  Luck            = " << player->getLck() << endl;
	this_thread::sleep_for(chrono::milliseconds(50));
	cout << "  Stamina         = " << player->getPp() << endl;
	this_thread::sleep_for(chrono::milliseconds(50));
	cout << "  Crit Chance     = " << player->getCritPercent() << "%" << endl;
	this_thread::sleep_for(chrono::milliseconds(50));
	cout << "  Dodge Chance    = " << player->getDodgePercent() << "%" << endl;
	this_thread::sleep_for(chrono::milliseconds(50));
	cout << "  Experience      = " << player->getExp() << endl;
	this_thread::sleep_for(chrono::milliseconds(50));
	cout << "  Level           = " << player->getLevel() << endl;
	this_thread::sleep_for(chrono::milliseconds(50));
	cout << "  Next Level At   = " << player->nextLevel() << endl;
	this_thread::sleep_for(chrono::milliseconds(50));
	cout << "  Gold            = " << player->getGold() << endl;
	this_thread::sleep_for(chrono::milliseconds(50));
	cout << "  ------------------------" << endl;
}

void System::levelUp(int points) {
	const int FIREWORK_WIDTH = 41;
	const int FIREWORK_HEIGHT = 5;
	string output = "";
	output += "     . : .                       . : .   ";
	output += "   .   :   .                   .   :   . ";
	output += "  .  ' : '  . YOU LEVELED UP! .  ' : '  .";
	output += "   .   :   .                   .   :   . ";
	output += "     ' : '                       ' : '   ";

	cout << endl;
	for (auto i = 0; i < FIREWORK_HEIGHT; i++) {
		cout << output.substr(FIREWORK_WIDTH * i, FIREWORK_WIDTH) << endl;
		this_thread::sleep_for(chrono::milliseconds(50));
	}
	this_thread::sleep_for(chrono::seconds(2));

	statPointDistribution(points);
}

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

	if (prevRoomDir == RoomExit::UP) output.at(ROOM_WIDTH / 2 + LEFT_MARGIN / 2 + ROOM_WIDTH) = 'P';
	else if (prevRoomDir == RoomExit::RIGHT) output.at(ROOM_WIDTH * (ROOM_HEIGHT / 2 + 1) - 3) = 'P';
	else if (prevRoomDir == RoomExit::DOWN) output.at((ROOM_WIDTH / 2) + (ROOM_HEIGHT - 2) * ROOM_WIDTH + LEFT_MARGIN / 2) = 'P';
	else if (prevRoomDir == RoomExit::LEFT) output.at(ROOM_WIDTH * (ROOM_HEIGHT / 2) + LEFT_MARGIN + 2) = 'P';

	cout << endl;
	for (int i = 0; i < ROOM_HEIGHT; i++) {
		cout << output.substr(ROOM_WIDTH * i, ROOM_WIDTH) << endl;
		this_thread::sleep_for(chrono::milliseconds(50));
	}
}

void System::statPointDistribution(int points) {
	playerSpecs();

	cout << endl;
	cout << "  You have " << points << " available stat points." << endl;
	this_thread::sleep_for(chrono::milliseconds(50));
	cout << "  Enter '1' to increase HEALTH   +5" << endl;
	this_thread::sleep_for(chrono::milliseconds(50));
	cout << "  Enter '2' to increase STRENGTH +1" << endl;
	this_thread::sleep_for(chrono::milliseconds(50));
	cout << "  Enter '3' to increase DEFENSE  +1" << endl;
	this_thread::sleep_for(chrono::milliseconds(50));
	cout << "  Enter '4' to increase SPEED    +1" << endl;
	this_thread::sleep_for(chrono::milliseconds(50));
	cout << "  Enter '5' to increase LUCK     +1" << endl;
	this_thread::sleep_for(chrono::milliseconds(50));
	cout << "  Enter '6' to increase STAMINA  +1" << endl;

	const int ARG = points;
	for (auto i = 0; i < ARG; i++) {
		int key = 0;
		cin >> key;

		this_thread::sleep_for(chrono::milliseconds(50));

		switch (key) {
		case 1:
			player->setHp(5);
			cout << "  Your health has increased! Health = " << player->getHp() << endl;
			points--;
			break;
		case 2:
			player->setStr(1);
			cout << "  Your strength has increased! Strength = " << player->getStr() << endl;
			points--;
			break;
		case 3:
			player->setDef(1);
			cout << "  Your defense has increased! Defense = " << player->getDef() << endl;
			points--;
			break;
		case 4:
			player->setSpd(1);
			cout << "  Your speed has increased! Speed = " << player->getSpd() << endl;
			points--;
			break;
		case 5:
			player->setLck(1);
			cout << "  Your luck has increased! Luck = " << player->getLck() << endl;
			points--;
			break;
		case 6:
			player->setPp(2);
			cout << "  Your stamina has increased! Stamina = " << player->getPp() << endl;
			points--;
			break;
		default:
			cout << "  Trying to break the system, eh?" << endl;
			i--;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;
		}

		this_thread::sleep_for(chrono::milliseconds(50));
		cout << "  You have " << points << " available stat points." << endl;
	}
	this_thread::sleep_for(chrono::milliseconds(50));

	playerSpecs();
}

#endif

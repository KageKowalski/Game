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
#include "TestStage.hpp"

using namespace std;

class System {

private:

	// Player
	Player* player;

	// All possible traversal directions
	enum class TraversalDir {
		UP,
		RIGHT,
		DOWN,
		LEFT
	};

	// Contains every stage in the game
	vector<Stage*> stages;
	
	// Current stage ID
	int currStageID;

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

	void overworld();

	void traverse(TraversalDir dir);

	void helpList() const;

};

int System::run() {
	int retCode = 0;

	init();

	overworld();
	
	return retCode;
}

void System::init() {
	player = &Player::get();
	stages.push_back(&TestStage::get());
	currStageID = TestStage::get().get_id();
}

void System::shutDown() {
	this_thread::sleep_for(chrono::seconds(3));
}

void System::playerSpecs() const {
	cout << endl;
	cout << "  ----- PLAYER SPECS -----" << endl;
	cout << "  Health         = " << player->getHp() << endl;
	cout << "  Strength        = " << player->getStr() << endl;
	cout << "  Defense         = " << player->getDef() << endl;
	cout << "  Speed           = " << player->getSpd() << endl;
	cout << "  Luck            = " << player->getLck() << endl;
	cout << "  Stamina         = " << player->getPp() << endl;
	cout << "  Crit Chance     = " << player->getCritPercent() << "%" << endl;
	cout << "  Dodge Chance    = " << player->getDodgePercent() << "%" << endl;
	cout << "  Experience      = " << player->getExp() << endl;
	cout << "  Level           = " << player->getLevel() << endl;
	cout << "  Next Level At   = " << player->nextLevel() << endl;
	cout << "  Gold            = " << player->getGold() << endl;
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
	}
	this_thread::sleep_for(chrono::seconds(1));

	statPointDistribution(points);
}

void System::drawRoom(const vector<RoomExit>& roomExits, const vector<RoomEntity>& roomEntities,
	const pair<int, int>& numEntites, RoomExit prevRoomDir) const {
	const int ROOM_WIDTH = 24;
	const int ROOM_HEIGHT = 9;
	const int LEFT_MARGIN = 3;
	string output = "";
	output += "    ------------------- ";
	output += "   |                   |";
	output += "   |                   |";
	output += "   |                   |";
	output += "   |                   |";
	output += "   |                   |";
	output += "   |                   |";
	output += "   |                   |";
	output += "    ------------------- ";

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
		else if(roomEntities.at(0) == RoomEntity::INTERACTABLE) {
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
	}
}

void System::statPointDistribution(int points) {
	playerSpecs();

	cout << endl;
	cout << "  You have " << points << " available stat points." << endl;
	cout << "  Enter '1' to increase HEALTH   +5" << endl;
	cout << "  Enter '2' to increase STRENGTH +1" << endl;
	cout << "  Enter '3' to increase DEFENSE  +1" << endl;
	cout << "  Enter '4' to increase SPEED    +1" << endl;
	cout << "  Enter '5' to increase LUCK     +1" << endl;
	cout << "  Enter '6' to increase STAMINA  +1" << endl;

	const int ARG = points;
	for (auto i = 0; i < ARG; i++) {
		int key = 0;
		cin >> key;

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
		cout << "  You have " << points << " available stat points." << endl;
	}

	playerSpecs();
}

void System::overworld() {
	while (true) {
		drawRoom(stages.at(currStageID)->get_room_exits(), stages.at(currStageID)->get_room_entities(),
			stages.at(currStageID)->get_num_entities(), stages.at(currStageID)->get_prev_room_dir());

		cout << endl;
		string input = "";
		cin >> input;

		for (auto i = 0; i < input.size(); i++)
			if (input.at(i) >= 'A' && input.at(i) <= 'Z') input.at(i) += 32;

		if (input == "h" || input == "help") {
			helpList();
		}
		else if(input == "n" || input == "north") {
			traverse(TraversalDir::UP);
		}
		else if (input == "e" || input == "east") {
			traverse(TraversalDir::RIGHT);
		}
		else if (input == "s" || input == "south") {
			traverse(TraversalDir::DOWN);
		}
		else if (input == "w" || input == "west") {
			traverse(TraversalDir::LEFT);
		}
		else {
			cout << "  Tongue tied?" << endl;			
		}
	}
}

void System::traverse(TraversalDir dir) {
	int result;
	switch (dir) {
	case TraversalDir::UP:
		result = TestStage::get().move_north();
		break;
	case TraversalDir::RIGHT:
		result = TestStage::get().move_east();
		break;
	case TraversalDir::DOWN:
		result = TestStage::get().move_south();
		break;
	case TraversalDir::LEFT:
		result = TestStage::get().move_west();
		break;
	}

	if (result == 1) {
		cout << "  There's a wall in the way!" << endl;
	}
	else if (result == 2) {
		cout << "  A monster guards the path." << endl;
	}
}

void System::helpList() const {
	cout << endl;
	cout << "  --- LIST OF COMMANDS ---" << endl;
	cout << "  [Always]" << endl;
	cout << "  help,    h" << endl;
	cout << endl << "  [Overworld]" << endl;
	cout << "  north,   n" << endl;
	cout << "  east,    e" << endl;
	cout << "  south,   s" << endl;
	cout << "  west,    w" << endl;
	cout << "  ------------------------" << endl;
}

#endif

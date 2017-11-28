#ifndef _SYSTEM
#define _SYSTEM 1

#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <string>
#include <limits>
#include <sstream>

#include "Player.hpp"
#include "RoomSpecifiers.hpp"
#include "TestStage.hpp"
#include "Monster.hpp"

using namespace std;

class System {

private:

	// All possible traversal directions
	enum class TraversalDir {
		UP,
		RIGHT,
		DOWN,
		LEFT
	};

	// All possible game states
	enum class GameState {
		FREEROAM,
		BATTLE,
		DEAD
	};

	// Contains game settings
	struct Settings {

		// All possible text speeds
		enum class TextSpeed {
			VERY_SLOW,
			SLOW,
			MODERATE,
			FAST,
			VERY_FAST,
			INSTANT
		};

		// Current text speed
		TextSpeed textSpeed;

		// Default constructor
		Settings() : textSpeed(TextSpeed::FAST) {}

		// Returns text speed as a string
		string printTextSpeed() const {
			switch (textSpeed) {
			case TextSpeed::VERY_SLOW:
				return "Very Slow";
			case TextSpeed::SLOW:
				return "Slow";
			case TextSpeed::MODERATE:
				return "Moderate";
			case TextSpeed::FAST:
				return "Fast";
			case TextSpeed::VERY_FAST:
				return "Very Fast";
			case TextSpeed::INSTANT:
				return "Instant";
			}
		}
	};

	// Player
	Player* player;

	// Contains every stage in the game
	vector<Stage*> stages;
	
	// Current stage ID
	int currStageID;

	// Game settings
	Settings settings;

	// Current state that the game is in
	GameState gameState;

	// Is debug mode enabled?
	bool debug;

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

	// Draws the current room
	void drawRoom(const vector<RoomExit>& roomExits, const vector<RoomEntity>& roomEntities,
		const pair<int, int>& numEntities, RoomExit prevRoomDir) const;

	GameState overworld();

	// Traverse the current stage
	void traverse(TraversalDir dir);

	// Prints list of all commands
	void helpList() const;

	// Configure game settings
	void configure();

	// Prints game settings
	void gameSettings() const;

	// Intro sequence
	void introSequence();

	// Prints a string of text with a time delay between each character depending on settings.textSpeed
	void printDelay(string output) const;

	// Prints a string of text with a time delay between each character depending on textSpeedOverride
	void printDelay(string output, Settings::TextSpeed textSpeedOverride) const;

	// Thread sleeps depending on settings.textSpeed
	void sleep() const;

	// Thread sleeps depending on textSpeedOverride
	void sleep(Settings::TextSpeed textSpeedOverride) const;

	// Thread sleeps for milliseconds, simulating an extended pause
	void sleep(int milliseconds) const;

	// Battle sequence
	bool battle(Monster* monster);

	// Asks to play again after death
	bool death() const;

	// Sets up the game
	void setUp();

	// Player attack logic
	bool playerAttack(Monster* monster);

	// Monster attack logic
	bool monsterAttack(Monster* monster);

	// Converts capital letters to lowercase letters in string
	void toLowerCase(string& str);
	
	// Wraps up a battle after victory
	void victory(Monster* monster);

	// Allows player to enter an array of extra commands which manipulate the game in some way
	// Toggles debug mode for easy debugging
	void toggleDebugMode();

	// Prints list of all debug commands
	void debugHelpList() const;

	// DEBUG: Heals the player
	void heal(int hp);

	// DEBUG: Damages the player
	void damage(int hp);
	
};

int System::run() {
	int retCode = 0;

	setUp();

	bool exit = false;

	while (!exit) {
		gameState = overworld();

		if (gameState == GameState::DEAD) {
			if (death()) exit = true;
			else exit = true;
		}
	}
	
	return retCode;
}

void System::init() {
	player = &Player::get();
	stages.push_back(&TestStage::get());
	currStageID = TestStage::get().get_id();
	gameState = GameState::FREEROAM;
	debug = false;
}

void System::shutDown() {
	sleep(2000);
}

void System::playerSpecs() const {
	cout << endl;
	cout << "  -------- PLAYER SPECS --------" << endl;
	cout << "  Name            = " << player->getName() << endl;
	cout << "  Max Health      = " << player->getHp() << " + " << player->get_hp_boost() << endl;
	cout << "  Health          = " << player->get_cur_hp() << endl;
	cout << "  Strength        = " << player->getStr() << " + " << player->get_str_boost() << endl;
	cout << "  Defense         = " << player->getDef() << " + " << player->get_def_boost() << endl;
	cout << "  Speed           = " << player->getSpd() << " + " << player->get_spd_boost() << endl;
	cout << "  Luck            = " << player->getLck() << " + " << player->get_lck_boost() << endl;
	cout << "  Stamina         = " << player->getPp() << endl;
	cout << "  Crit Chance     = " << player->getCritPercent() << "%" << endl;
	cout << "  Dodge Chance    = " << player->getDodgePercent() << "%" << endl;
	cout << "  Experience      = " << player->getExp() << endl;
	cout << "  Next Level At   = " << player->nextLevel() << endl;
	cout << "  Level           = " << player->getLevel() << endl;
	cout << "  Gold            = " << player->getGold() << endl;
	cout << "  ------------------------------" << endl;
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
	sleep(1000);

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
	else if (prevRoomDir == RoomExit::NONE) output.at(ROOM_WIDTH * ROOM_HEIGHT / 2 + 1) = 'P';

	cout << endl;
	for (int i = 0; i < ROOM_HEIGHT; i++) {
		cout << output.substr(ROOM_WIDTH * i, ROOM_WIDTH) << endl;
	}
}

void System::statPointDistribution(int points) {
	playerSpecs();

	ostringstream output;
	output << "\\n  You have " << points << " available stat points.\\n  Enter '1' to increase HEALTH   +5\\n"
		<< "  Enter '2' to increase STRENGTH +1\\n  Enter '3' to increase DEFENSE  +1\\n"
		<< "  Enter '4' to increase SPEED    +1\\n  Enter '5' to increase LUCK     +1\\n"
		<< "  Enter '6' to increase STAMINA  +2\\n\\n";
	printDelay(output.str());
	output.str("");

	const int ARG = points;
	for (auto i = 0; i < ARG; i++) {
		int key = 0;
		cin >> key;

		switch (key) {
		case 1:
			player->setHp(5);
			player->change_cur_hp(5);
			output << "\\n  Your health has increased! Health = " << player->getHp() << "\\n";
			points--;
			break;
		case 2:
			player->setStr(1);
			output << "\\n  Your strength has increased! Strength = " << player->getStr() << "\\n";
			points--;
			break;
		case 3:
			player->setDef(1);
			output << "\\n  Your defense has increased! Defense = " << player->getDef() << "\\n";
			points--;
			break;
		case 4:
			player->setSpd(1);
			output << "\\n  Your speed has increased! Speed = " << player->getSpd() << "\\n";
			points--;
			break;
		case 5:
			player->setLck(1);
			output << "\\n  Your luck has increased! Luck = " << player->getLck() << "\\n";
			points--;
			break;
		case 6:
			player->setPp(2);
			output << "\\n  Your stamina has increased! Stamina = " << player->getPp() << "\\n";
			points--;
			break;
		default:
			output << "\\n  Trying to break the system, eh?" << "\\n";
			i--;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;
		}
		printDelay(output.str());
		output.str("");

		output << "\\n  You have " << points << " available stat points." << "\\n\\n";
		printDelay(output.str());
		output.str("");
	}

	playerSpecs();
}

System::GameState System::overworld() {
	GameState ret = System::GameState::FREEROAM;

	drawRoom(stages.at(currStageID)->get_room_exits(), stages.at(currStageID)->get_room_entities(),
		stages.at(currStageID)->get_num_entities(), stages.at(currStageID)->get_prev_room_dir());
	printDelay("  " + stages.at(currStageID)->get_description() + "\\n");

	cout << endl;
	string input = "";
	cin >> input;

	toLowerCase(input);

	if (input == "h" || input == "help") helpList();
	else if (input == "c" || input == "configure") configure();
	else if (input == "se" || input == "settings") gameSettings();
	else if (input == "sp" || input == "specs") playerSpecs();
	else if (debug && (input == "dhelp" || input == "dh")) debugHelpList();
	else if (input == "n" || input == "north") traverse(TraversalDir::UP);
	else if (input == "e" || input == "east") traverse(TraversalDir::RIGHT);
	else if (input == "s" || input == "south") traverse(TraversalDir::DOWN);
	else if (input == "w" || input == "west") traverse(TraversalDir::LEFT);
	else if (input == "inspect" || input == "i") {

	}
	else if (input == "fight" || input == "f") {
		vector<Monster> monsters = stages.at(currStageID)->get_monsters();
		if (monsters.size() == 0) printDelay("  There's nothing to fight!\\n");
		else {
			Monster currMonster = monsters.at(0);
			if (battle(&currMonster)) {
				victory(&currMonster);
				stages.at(currStageID)->remove_monster(currMonster);
			}
			else ret = GameState::DEAD;
		}
	}
	else if (input == "inventory" || input == "in") {

	}
	else if (input == "d" || input == "debug") {
		if (debug == false) {
			printDelay("\\n  Enter access code: ");
			string code;
			cin >> code;

			if (code == "112117") {
				toggleDebugMode();
				printDelay("  Debug mode enabled.\\n");
			}
			else printDelay("  Incorrect code.\\n");
		}
		else {
			toggleDebugMode();
			printDelay("\\n  Debug mode disabled.\\n");
		}
	}
	else if (debug && input.size() >= 7 && input.substr(0, 4) == "heal") {
		bool valid = true;
		string arg = input.substr(5, input.size() - 1 - 5);
		
		if (input.back() != ')') valid = false;
		for (int i = 0; i < arg.size(); i++) if (arg.at(i) < '0' || arg.at(i) > '9') valid = false;

		if (valid) {
			int arg = atoi(input.substr(5, input.size() - 1 - 5).c_str());
			heal(arg);
		}
		else printDelay("\\n  Argument not recognized.\\n");
	}
	else if (debug && input.size() >= 9 && input.substr(0, 6) == "damage") {
		bool valid = true;
		string arg = input.substr(7, input.size() - 1 - 7);

		if (input.back() != ')') valid = false;
		for (int i = 0; i < arg.size(); i++) if (arg.at(i) < '0' || arg.at(i) > '9') valid = false;

		if (valid) {
			int arg = atoi(input.substr(7, input.size() - 1 - 7).c_str());
			damage(arg);
		}
		else printDelay("\\n  Argument not recognized.\\n");
	}
	else printDelay("\\n  Tongue tied? Try typing 'h'!\\n");

	return ret;
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

	if (result == 1) printDelay("  There's a wall in the way!\\n");
	else if (result == 2) printDelay("  A monster guards the path.\\n");
}

void System::helpList() const {
	cout << endl << "  --- LIST OF COMMANDS ---" << endl;
	cout << "  [Always]" << endl;
	cout << "  help        h" << endl;
	cout << "  configure   c" << endl;
	cout << "  settings    se" << endl;
	cout << "  specs       sp" << endl;
	if(debug) cout << "  dhelp       dh" << endl;
	cout << endl << "  [Overworld]" << endl;
	cout << "  north       n" << endl;
	cout << "  east        e" << endl;
	cout << "  south       s" << endl;
	cout << "  west        w" << endl;
	cout << "  inspect     i" << endl;
	cout << "  fight       f" << endl;
	cout << "  inventory   in" << endl;
	cout << "  debug       d" << endl;
	cout << endl << "  [Battle]" << endl;
	cout << "  attack      a" << endl;
	cout << "  ------------------------" << endl;
}

void System::configure() {
	gameSettings();

	ostringstream output;
	output << "  TEXT SPEED" << "\n";
	output << "  Enter '1' for Very Slow" << "\n";
	output << "  Enter '2' for Slow" << "\n";
	output << "  Enter '3' for Moderate" << "\n";
	output << "  Enter '4' for Fast" << "\n";
	output << "  Enter '5' for Very Fast" << "\n";
	output << "  Enter '6' for Instant" << "\n";
	printDelay(output.str());
	output.str("");
	
	bool loop = true;
	while (loop) {
		int key = 0;
		cin >> key;

		switch (key) {
		case 1:
			settings.textSpeed = Settings::TextSpeed::VERY_SLOW;
			loop = false;
			break;
		case 2:
			settings.textSpeed = Settings::TextSpeed::SLOW;
			loop = false;
			break;
		case 3:
			settings.textSpeed = Settings::TextSpeed::MODERATE;
			loop = false;
			break;
		case 4:
			settings.textSpeed = Settings::TextSpeed::FAST;
			loop = false;
			break;
		case 5:
			settings.textSpeed = Settings::TextSpeed::VERY_FAST;
			loop = false;
			break;
		case 6:
			settings.textSpeed = Settings::TextSpeed::INSTANT;
			loop = false;
			break;
		default:
			output << "  This is serious stuff, you know..." << "\n";
			printDelay(output.str());
			output.str("");

			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;
		}
	}

	gameSettings();
}

void System::gameSettings() const {
	cout << endl;
	cout << "  ----- GAME SETTINGS -----" << endl;
	cout << "  Text Speed = " << settings.printTextSpeed() << endl;
	cout << "  -------------------------" << endl << endl;
}

void System::introSequence() {
	printDelay("\\n  Enter a startup code: ");
	string code;
	getline(cin, code);
	
	vector<string> codes;
	size_t index = 0;
	while ((index = code.find(' ')) != string::npos) {
		codes.push_back(code.substr(0, index));
		code.erase(0, index + 1);
	}
	codes.push_back(code);

	bool skipIntro = false;
	while (codes.size() > 0) {
		if (codes.front() == "skipintro") skipIntro = true;
		else if (codes.front() == "startindebugmode") toggleDebugMode();
		codes.erase(codes.cbegin());
	}
	if (skipIntro) return;

	printDelay("\\n  ...Hello?", Settings::TextSpeed::VERY_SLOW);
	printDelay("\\n\\n  ...You there...", Settings::TextSpeed::SLOW);
	printDelay("\\n\\n  ...What's your name?\\n\\n", Settings::TextSpeed::MODERATE);

	string name;
	getline(cin, name);
	player->setName(name);

	statPointDistribution(15);
}

void System::printDelay(string output) const {
	for (auto i = 0; i < output.size(); i++) {
		if (i < output.size() - 1 && output.substr(i, 2) == "\\n") {
			cout << endl;
			i++;
		}
		else {
			cout << output.at(i);
			if (output.at(i) != ' ') sleep();
		}
	}
}

void System::printDelay(string output, Settings::TextSpeed textSpeedOverride) const {
	for (auto i = 0; i < output.size(); i++) {
		if (i < output.size() - 1 && output.substr(i, 2) == "\\n") {
			cout << endl;
			i++;
		}
		else {
			cout << output.at(i);
			if (output.at(i) != ' ') sleep(textSpeedOverride);
		}
	}
}

void System::sleep() const {
	switch (settings.textSpeed) {
	case Settings::TextSpeed::VERY_SLOW:
		this_thread::sleep_for(chrono::milliseconds(500));
		break;
	case Settings::TextSpeed::SLOW:
		this_thread::sleep_for(chrono::milliseconds(250));
		break;
	case Settings::TextSpeed::MODERATE:
		this_thread::sleep_for(chrono::milliseconds(60));
		break;
	case Settings::TextSpeed::FAST:
		this_thread::sleep_for(chrono::milliseconds(15));
		break;
	case Settings::TextSpeed::VERY_FAST:
		this_thread::sleep_for(chrono::milliseconds(5));
		break;
	}
}

void System::sleep(Settings::TextSpeed textSpeedOverride) const {
	switch (textSpeedOverride) {
	case Settings::TextSpeed::VERY_SLOW:
		this_thread::sleep_for(chrono::milliseconds(500));
		break;
	case Settings::TextSpeed::SLOW:
		this_thread::sleep_for(chrono::milliseconds(250));
		break;
	case Settings::TextSpeed::MODERATE:
		this_thread::sleep_for(chrono::milliseconds(60));
		break;
	case Settings::TextSpeed::FAST:
		this_thread::sleep_for(chrono::milliseconds(15));
		break;
	case Settings::TextSpeed::VERY_FAST:
		this_thread::sleep_for(chrono::milliseconds(5));
		break;
	}
}

void System::sleep(int milliseconds) const {
	this_thread::sleep_for(chrono::milliseconds(milliseconds));
}

bool System::battle(Monster* monster) {
	const int SWORD_WIDTH = 29;
	const int SWORD_HEIGHT = 3;
	string output = "";
	output += "        /| _________________ ";
	output += "  O|===|* >______FIGHT______>";
	output += "        \\|                   ";

	cout << endl;
	for (auto i = 0; i < SWORD_HEIGHT; i++) {
		cout << output.substr(SWORD_WIDTH * i, SWORD_WIDTH) << endl;
	}
	sleep(1000);

	printDelay("\\n  " + player->getName() + " Lv. " + to_string(player->getLevel()) + "  VS  "
		+ monster->getName() + " Lv. " + to_string(monster->getLvl()) + "\\n\\n");

	string input;
	while (true) {
		printDelay("  " + player->getName() + ": " + to_string(player->get_cur_hp()) + "  "
			+ monster->getName() + ": " + to_string(monster->getHp()) + "\\n  It's your call...\\n");
		cout << "  |attack|" << endl << endl;
		cin >> input;

		toLowerCase(input);

		if (input == "a" || input == "attack") {
			if (player->getSpd() >= monster->getSpd()) {
				if (playerAttack(monster)) return true;
				if (monsterAttack(monster)) return false;
			}
			else {
				if (monsterAttack(monster)) return false;
				if (playerAttack(monster)) return true;
			}
		}
		else printDelay("  Do not fool around while in combat!\\n");
		cout << endl;
	}
}

bool System::death() const {
	const int SKULL_WIDTH = 30;
	const int SKULL_HEIGHT = 6;
	string output = "";
	output += "    _____              _____  ";
	output += "   /     \\            /     \\ ";
	output += "  | () () | YOU DIED | () () |";
	output += "   \\  ^  /            \\  ^  / ";
	output += "    |||||              |||||  ";
	output += "    |||||              |||||  ";

	cout << endl;
	for (auto i = 0; i < SKULL_HEIGHT; i++) {
		cout << output.substr(SKULL_WIDTH * i, SKULL_WIDTH) << endl;
	}
	sleep(1000);

	printDelay("\\n  Try again?\\n  Enter '1' for a better run.\\n  Enter '2' if you have homework to do.\\n");

	while (true) {
		int key = 0;
		cin >> key;

		switch (key) {
		case 1:
			return true;
		case 2:
			return false;
		default:
			printDelay("  Hesitant? It's tempting to give it another go!\\n");
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;
		}
	}
}

void System::setUp() {
	init();
	introSequence();
}

bool System::playerAttack(Monster* monster) {
	pair<int, bool> atRet;

	bool monsterDodged = monster->rollDodge();
	if (monsterDodged) printDelay("\\n  " + monster->getName() + " dodged the attack!");
	else {
		atRet = player->attack(*monster);

		if (atRet.second == false)
			printDelay("\\n  You dealt " + to_string(atRet.first) + " damage to "
				+ monster->getName() + "!\\n");
		else printDelay("\\n  You dealt a whopping" + to_string(atRet.first) + " damage to "
			+ monster->getName() + "!\\n");
		sleep(1000);

		if (monster->isDead()) return true;
	}

	return false;
}

bool System::monsterAttack(Monster* monster) {
	pair<int, bool> atRet;

	bool playerDodged = player->rollDodge();
	if (playerDodged) printDelay("\\n  You dodged the attack!");
	else {
		atRet = monster->attack_player(*player);

		if (atRet.second == false)
			printDelay("\\n  " + monster->getName() + " dealt " + to_string(atRet.first)
				+ " damage to you!\\n");
		else printDelay("\\n  " + monster->getName() + " dealt a whopping " + to_string(atRet.first)
			+ " damage to you!\\n");

		if (player->isDead()) return true;
	}

	return false;
}

void System::toLowerCase(string& str) {
	for (auto i = 0; i < str.size(); i++)
		if (str.at(i) >= 'A' && str.at(i) <= 'Z') str.at(i) += 32;
}

void System::victory(Monster* monster) {
	const int V_WIDTH = 10;
	const int V_HEIGHT = 3;
	string output = "";
	output += "  \\\\    //";
	output += "   \\\\  // ";
	output += "    \\\\//  ";

	cout << endl;
	for (auto i = 0; i < V_HEIGHT - 1; i++) {
		cout << output.substr(V_WIDTH * i, V_WIDTH) << endl;
	}
	cout << output.substr(V_WIDTH * (V_HEIGHT - 1), V_WIDTH) << "ICTORY!" << endl << endl;
	sleep(1000);

	int levelUpRec = player->increaseExp(monster->getExp());
	printDelay("  You gained " + to_string(monster->getExp()) + " experience!\\n");
	sleep(1000);

	for (auto i = levelUpRec; i > 0; i--) levelUp(3);
}

void System::toggleDebugMode() {
	debug = !debug;
}

void System::debugHelpList() const {
	cout << endl << "  --- LIST OF DEBUG COMMANDS ---" << endl;
	cout << "  [Always]" << endl;
	cout << "  heal(X)      [MAX: " << player->get_hp_tot() - player->get_cur_hp() << "]" << endl;
	cout << "  damage(X)    [MAX: " << player->get_cur_hp() - 1 << "]" << endl;
	cout << endl << "  [Startup]" << endl;
	cout << "  skipintro" << endl;
	cout << "  startindebugmode" << endl;
	cout << "  ------------------------------" << endl;
}

void System::heal(int hp) {
	if (hp < 1 || hp > player->get_hp_tot() - player->get_cur_hp())
		printDelay("\\n  Argument out of bounds.\\n");
	else {
		player->change_cur_hp(hp);
		printDelay("\\n  Player healed " + to_string(hp) + " points.\\n");
	}
}

void System::damage(int hp) {
	if (hp < 1 || hp > player->get_cur_hp() - 1)
		printDelay("\\n  Argument out of bounds.\\n");
	else {
		player->change_cur_hp(-hp);
		printDelay("\\n  Player damaged " + to_string(hp) + " points.\\n");
	}
}

#endif

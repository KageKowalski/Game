#include <string>
#include <pair>
#include "Room.hpp"

class Stage{
	public:
		//  Initializes this stage as beginning at room with id=0.
		Stage(): curRoom(0) {}

		
		//  Returns all info regarding the current room of this stage in the format:
		//			[north, east, south, west, combatant, interactable]
		//  For directions, a 1 denotes that the player can move in that direction, a 0 denotes that they can't.
		//  For combatant and interactable, the count of combatants or interactables found in the current room is passed.
		vector<int> cur_room_info();

		
		//  Moves the player north, east, south, and west.
		//  Returns true if success, otherwise false.
		bool move_north();
		bool move_east();
		bool move_south();
		bool move_west();


		//  Returns a vector of the combatants or interactables found in the current room paired with their id numbers.
		vector<pair<Combatant, int>> get_combatant();
		vector<pair<Interactable, int>> get_interactable();


		//  Removes combatant or interactable from the current room based on passed id number.
		//  Returns true if success, otherwise false.
		bool remove_combatant(int id);
		bool remove_interactable(int id);
	protected:
		int curRoom;
		vector<Room> rooms;
}


vector<int> Stage::cur_room_info(){
	vector<int> data;
	data.push_back(rooms.at(curRoom).has_north() == true);
	data.push_back(rooms.at(curRoom).has_east() == true);
	data.push_back(rooms.at(curRoom).has_south() == true);
	data.push_back(rooms.at(curRoom).has_west() == true);
	data.push_back(rooms.at(curRoom).get_num_combatants);
	data.push_back(rooms.at(curRoom).get_num_interactables);
	return data;
}


bool Stage::move_north(){
	if(!rooms.at(curRoom).has_north()) return false;
	curRoom = rooms.at(curRoom).get_north();
	return true;
}


bool Stage::move_east(){
	if(!rooms.at(curRoom).has_east()) return false;
	curRoom = rooms.at(curRoom).get_east();
	return true;
}


bool Stage::move_south(){
	if(!rooms.at(curRoom).has_south()) return false;
	curRoom = rooms.at(curRoom).get_south();
	return true;
}


bool Stage::move_west(){
	if(!rooms.at(curRoom).has_west()) return false;
	curRoom = rooms.at(curRoom).get_west();
	return true;
}








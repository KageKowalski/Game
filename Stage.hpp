#include <string>
#include "Room.hpp"

class Stage{
	public:
		//  Initializes this Stage as beginning at Room with id=0 and nonexistent prevRoom id.
		Stage(): curRoom(0), prevRoom(-1) {}

		
		//  Returns all info regarding the current Room of this Stage in the format:
		//			[north, east, south, west, Monster, Interactable]
		//  For directions, a 1 denotes that the Player can move in that direction, a 0 denotes that they can't.
		//  For Monster and Interactable, the count of Monsters or Interactables found in the current Room is passed.
		vector<int> cur_room_info();

		
		//  Moves the Player north, east, south, or west.
		//  Returns 0 if successful, 1 if no exit exists in the chosen direction, 2 if a monster is blocking the player's route.
		int move_north();
		int move_east();
		int move_south();
		int move_west();


		//  Returns a vector of the Monsters or Interactables found in the current Room.
		vector<Monster*> get_monsters();
		vector<Interactable*> get_interactables();


		//  Removes Monster or Interactable from the current Room based on passed pointer.
		//  Returns true if successful, otherwise false.
		bool remove_monster(Monster*);
		bool remove_interactable(Interactable*);


	protected:
		int curRoom;
		int prevRoom;
		vector<Room> rooms;
};


//  INFORMATION METHOD


vector<int> Stage::cur_room_info(){
	vector<int> data;
	data.push_back(rooms.at(curRoom).has_north() == true);
	data.push_back(rooms.at(curRoom).has_east() == true);
	data.push_back(rooms.at(curRoom).has_south() == true);
	data.push_back(rooms.at(curRoom).has_west() == true);
	data.push_back(rooms.at(curRoom).get_num_monsters());
	data.push_back(rooms.at(curRoom).get_num_interactables());
	return data;
}


//  MOVE METHODS
//
//  First if statement denies movement if the current Room doesn't have an exit in the direction the Player is attempting to move.
//  Second if statement denies movement if the current Room has Monsters AND the Player is attempting to move to a new Room.


int Stage::move_north(){
	if(!rooms.at(curRoom).has_north()) return 1;
	if(rooms.at(curRoom).get_num_monsters() && rooms.at(curRoom).get_north() != prevRoom) return 2;
	prevRoom = curRoom;
	curRoom = rooms.at(curRoom).get_north();
	return 0;
}


int Stage::move_east(){
	if(!rooms.at(curRoom).has_east()) return 1;
	if(rooms.at(curRoom).get_num_monsters() && rooms.at(curRoom).get_east() != prevRoom) return 2;
	prevRoom = curRoom;
	curRoom = rooms.at(curRoom).get_east();
	return 0;
}


int Stage::move_south(){
	if(!rooms.at(curRoom).has_south()) return 1;
	if(rooms.at(curRoom).get_num_monsters() && rooms.at(curRoom).get_south() != prevRoom) return 2;
	prevRoom = curRoom;
	curRoom = rooms.at(curRoom).get_south();
	return 0;
}


int Stage::move_west(){
	if(!rooms.at(curRoom).has_west()) return 1;
	if(rooms.at(curRoom).get_num_monsters() && rooms.at(curRoom).get_west() != prevRoom) return 2;
	prevRoom = curRoom;
	curRoom = rooms.at(curRoom).get_west();
	return 0;
}


//  GETTER METHODS


vector<Monster*> Stage::get_monsters(){
	return rooms.at(curRoom).get_monsters();
}


vector<Interactable*> Stage::get_interactables(){
	return rooms.at(curRoom).get_interactables();
}


//  MUTATOR METHODS


bool Stage::remove_monster(Monster* mo){
	return rooms.at(curRoom).remove_monster(mo);
}


bool Stage::remove_interactable(Interactable* in){
	return rooms.at(curRoom).remove_interactable(in);
}

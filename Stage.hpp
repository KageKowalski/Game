#ifndef _StageGuard
#define _StageGuard

#include <string>
#include "Room.hpp"
#include "RoomSpecifiers.hpp"

class Stage{
	public:
		//  Initializes this Stage as beginning at Room with id=0, nonexistent prevRoom id, and a name.
		Stage(): curRoom(0), prevRoom(-100) {}


		//  Moves the Player north, east, south, or west.
		//  Returns 0 if successful, 1 if no exit exists in the chosen direction, 2 if a monster is blocking the player's route, -1 if Stage exit is found.
		int move_north();
		int move_east();
		int move_south();
		int move_west();


		//  GETTERS
		//  get_monsters() returns address of vector pointers to Monsters in the current Room.
		//  get_interactables() returns address of vector of pointers to Interactables in the current Room.
		//  get_num_entities() returns a pair containing the number of Monsters in the current Room and the number of Interactables in the current Room, respectively.
		//  get_room_exits() returns a vector of RoomExits for the current Room.
		//  get_room_entities() returns a vector of RoomEntities for the current Room.
		//  get_prev_room_dir() returns the RoomExit (direction) of the previous room, relative to the current room. Returns RoomExit::NONE if previous room can't be found.
		//  get_name() returns the name of the current Room.
		//  get_description() returns the description of this Room.
		const vector<Monster*>& get_monsters() {return rooms.at(curRoom).get_monsters();}
		const vector<Interactable*>& get_interactables() {return rooms.at(curRoom).get_interactables();}
		pair<int, int> get_num_entities() {return pair<int, int>(rooms.at(curRoom).get_num_monsters(), rooms.at(curRoom).get_num_interactables());}
		vector<RoomExit> get_room_exits();
		vector<RoomEntity> get_room_entities();
		RoomExit get_prev_room_dir();
		string get_name() {return name;}
		int get_id() {return rooms.at(curRoom).get_id();}
		string get_description() {return rooms.at(curRoom).get_description();}


		//  Removes passed Monster or Interactable from the current Room.
		void remove_monster(Monster* mo) {rooms.at(curRoom).remove_monster(mo);}
		void remove_interactable(Interactable* in) {rooms.at(curRoom).remove_interactable(in);}


	protected:
		int curRoom;
		int prevRoom;
		vector<Room> rooms;
		string name;
};


//  MOVE METHODS
//
//  First if statement denies movement if the current Room doesn't have an exit in the direction the Player is attempting to move.
//  Second if statement denies movement if the current Room has Monsters AND the Player is attempting to move to a new Room.
//  Third if statement returns -1 if the Stage exit is found.


int Stage::move_north(){
	if(rooms.at(curRoom).get_north() == Room::DEAD_END) return 1;
	if(rooms.at(curRoom).get_num_monsters() && rooms.at(curRoom).get_north() != prevRoom) return 2;
	if(rooms.at(curRoom).get_north() == Room::STAGE_EXIT) return -1;
	prevRoom = curRoom;
	curRoom = rooms.at(curRoom).get_north();
	return 0;
}


int Stage::move_east(){
	if(rooms.at(curRoom).get_east() == Room::DEAD_END) return 1;
	if(rooms.at(curRoom).get_num_monsters() && rooms.at(curRoom).get_east() != prevRoom) return 2;
	if(rooms.at(curRoom).get_east() == Room::STAGE_EXIT) return -1;
	prevRoom = curRoom;
	curRoom = rooms.at(curRoom).get_east();
	return 0;
}


int Stage::move_south(){
	if(rooms.at(curRoom).get_south() == Room::DEAD_END) return 1;
	if(rooms.at(curRoom).get_num_monsters() && rooms.at(curRoom).get_south() != prevRoom) return 2;
	if(rooms.at(curRoom).get_south() == Room::STAGE_EXIT) return -1;
	prevRoom = curRoom;
	curRoom = rooms.at(curRoom).get_south();
	return 0;
}


int Stage::move_west(){
	if(rooms.at(curRoom).get_west() == Room::DEAD_END) return 1;
	if(rooms.at(curRoom).get_num_monsters() && rooms.at(curRoom).get_west() != prevRoom) return 2;
	if(rooms.at(curRoom).get_west() == Room::STAGE_EXIT) return -1;
	prevRoom = curRoom;
	curRoom = rooms.at(curRoom).get_west();
	return 0;
}


//  GETTER METHODS


vector<RoomExit> Stage::get_room_exits(){
	vector<RoomExit> roomExits;
	if(rooms.at(curRoom).has_north()) roomExits.push_back(RoomExit::UP);
	if(rooms.at(curRoom).has_east()) roomExits.push_back(RoomExit::RIGHT);
	if(rooms.at(curRoom).has_south()) roomExits.push_back(RoomExit::DOWN);
	if(rooms.at(curRoom).has_west()) roomExits.push_back(RoomExit::LEFT);
	if(roomExits.empty()) roomExits.push_back(RoomExit::NONE);
	return roomExits;
}


vector<RoomEntity> Stage::get_room_entities(){
	vector<RoomEntity> roomEntities;
	if(rooms.at(curRoom).get_num_monsters()) roomEntities.push_back(RoomEntity::MONSTER);
	if(rooms.at(curRoom).get_num_interactables()) roomEntities.push_back(RoomEntity::INTERACTABLE);
	if(roomEntities.empty()) roomEntities.push_back(RoomEntity::NONE);
	return roomEntities;
}


RoomExit Stage::get_prev_room_dir(){
	if(rooms.at(curRoom).get_north() == prevRoom) return RoomExit::UP;
	if(rooms.at(curRoom).get_east() == prevRoom) return RoomExit::RIGHT;
	if(rooms.at(curRoom).get_south() == prevRoom) return RoomExit::DOWN;
	if(rooms.at(curRoom).get_west() == prevRoom) return RoomExit::LEFT;
	return RoomExit::NONE;
}

#endif

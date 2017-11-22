#ifndef _RoomGuard
#define _RoomGuard

#include <vector>
#include <assert.h>
#include "Monster.hpp"
#include "Interactable.hpp"

class Room{
	public:
		//  Initializes all of this Room's data.
		Room(int _id, int _north, int _east, int _south, int _west):
			id(_id), north(_north), east(_east), south(_south), west(_west), description("") {}


		//  Return true if this Room has designated exit, else false.
		bool has_north() {return north != DEAD_END;}
		bool has_east() {return east != DEAD_END;}
		bool has_south() {return south != DEAD_END;}
		bool has_west() {return west != DEAD_END;}


		//  Return the int id of the designated Room, relative to this Room.
		int get_north() {return north;}
		int get_east() {return east;}
		int get_south() {return south;}
		int get_west() {return west;}
		int get_id() {return id;}


		//  Return number of Monsters or Interactables in this Room.
		int get_num_monsters() {return monsters.size();}
		int get_num_interactables() {return interactables.size();}


		//  Return address of vector of pointers to Monsters or Interactables in this Room.
		const vector<Monster*> get_monsters() {return monsters;}
		const vector<Interactable*> get_interactables() {return interactables;}


		//  Adds passed Monster or Interactable to this Room.
		void add_monster(Monster&);
		void add_interactable(Interactable&);


		//  Sets or gets this Room's description.
		void set_description(string _description) {description = _description;}
		string get_description() {return description;}


		//  Removes passed Monster or Interactable from this Room.
		void remove_monster(Monster*);
		void remove_interactable(Interactable*);

		
		//  Constants designating dead ends and stage exits.
		const static int DEAD_END   = -1;
		const static int STAGE_EXIT = -2;


	protected:
		int id;
		int north;
		int east;
		int south;
		int west;
		string description;
		vector<Monster*> monsters;
		vector<Interactable*> interactables;
};


//  MUTATORS


void Room::add_monster(Monster& mo){
	monsters.push_back(&mo);
}


void Room::add_interactable(Interactable& in){
	interactables.push_back(&in);
}


void Room::remove_monster(Monster* mo){
	vector<Monster*> updatedMonsters;
	bool monsterFound = false;
	for(int i = 0; i < monsters.size(); i++){
		if(monsters.at(i) != mo) updatedMonsters.push_back(monsters.at(i));
		else { monsterFound = true; }
	}
	monsters = updatedMonsters;
	assert(monsterFound);
}


void Room::remove_interactable(Interactable* in){
	vector<Interactable*> updatedInteractables;
	bool interactableFound = false;
	for(int i = 0; i < interactables.size(); i++){
		if(interactables.at(i) != in) updatedInteractables.push_back(interactables.at(i));
		else { interactableFound = true; }
	}
	interactables = updatedInteractables;
	assert(interactableFound);
}

#endif

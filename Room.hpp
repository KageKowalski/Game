#include <vector>
#include "Monster.hpp"
#include "Interactable.hpp"

class Room{
	public:
		//  Initializes all of this Room's data.
		Room(int _id, int _north, int _east, int _south, int _west, vector<Monster*> _monsters, vector<Interactable*> _interactables):
			id(_id), north(_north), east(_east), south(_south), west(_west), monsters(_monsters), interactables(_interactables) {}


		//  Return true if this Room has designated exit, else false.
		bool has_north() {return north != -1;}
		bool has_east() {return east != -1;}
		bool has_south() {return south != -1;}
		bool has_west() {return west != -1;}


		//  Return the int id of the designated Room, relative to this Room.
		int get_north() {return north;}
		int get_east() {return east;}
		int get_south() {return south;}
		int get_west() {return west;}


		//  Return number of Monsters or Interactables in this Room.
		int get_num_monsters() {return monsters.size();}
		int get_num_interactables() {return interactables.size();}


		//  Return vector of pointers to Monsters or Interactables in this Room.
		vector<Monster*> get_monsters() {return monsters;}
		vector<Interactable*> get_interactables() {return interactables;}


		//  Removes passed Monster or Interactable from this Room.
		//  Returns true if successful, else false.
		bool remove_monster(Monster*);
		bool remove_interactable(Interactable*);


	protected:
		int id;
		int north;
		int east;
		int south;
		int west;
		vector<Monster*> monsters;
		vector<Interactable*> interactables;
};


//  MUTATORS


bool Room::remove_monster(Monster* mo){
	vector<Monster*> updatedMonsters;
	bool monsterFound = false;
	for(int i = 0; i < monsters.size(); i++){
		if(monsters.at(i) != mo) updatedMonsters.push_back(monsters.at(i));
		else monsterFound = true;
	}
	monsters = updatedMonsters;
	return monsterFound;
}


bool Room::remove_interactable(Interactable* in){
	vector<Interactable*> updatedInteractables;
	bool interactableFound = false;
	for(int i = 0; i < interactables.size(); i++){
		if(interactables.at(i) != in) updatedInteractables.push_back(interactables.at(i));
		else interactableFound = true;
	}
	interactables = updatedInteractables;
	return interactableFound;
}

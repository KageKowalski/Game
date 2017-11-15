#include <vector>
#include "Monster.hpp"
#include "Interactable.hpp"

class Room{
	public:
		// Initializes this Room with id = _num.
		Room(int _num): id(_num) {}


		//  Return true if this Room has designated exit, else false.
		bool has_north();
		bool has_east();
		bool has_south();
		bool has_west();


		//  Return the int id of the designated Room, relative to this Room.
		int get_north();
		int get_east();
		int get_south();
		int get_west();


		//  Return number of Monsters or Interactables in this Room.
		int get_num_monsters();
		int get_num_interactables();


		//  Return vector of pointers to Monsters or Interactables in this Room.
		vector<Monster*> get_monsters();
		vector<Interactable*> get_interactables();


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

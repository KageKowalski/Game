#include <vector>
#include "Combatant.hpp"
#include "Interactable.hpp"

class Room{
	public:
		Room(int _num);
		bool has_north();
		bool has_east();
		bool has_south();
		bool has_west();
		int get_north();
		int get_east();
		int get_south();
		int get_west();
		int get_num_combatants();
		int get_num_interactables();
	protected:
		int id;
		int north;
		int east;
		int south;
		int west;

}

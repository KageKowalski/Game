#ifndef TestStage_h
#define TestStage_h

#include "Stage.hpp"
#include "Monsters/Slime.hpp"

class TestStage : public Stage{
	public:
		//  Singleton Design Pattern.
    	void operator=(TestStage const&) = delete;
    
    	static TestStage& get()
    	{
			static TestStage instance;
			return instance;
    	}

	private:
		//  Hard-code constructs this Stage.
		TestStage(){
			name = "Test Stage";

			Room room0(0, Room::DEAD_END, 1, Room::DEAD_END, Room::DEAD_END);
			rooms.push_back(room0);

			Room room1(1, 2, 3, Room::DEAD_END, 0);
			rooms.push_back(room1);

			Room room2(2, Room::DEAD_END, 4, 1, Room::DEAD_END);
			rooms.push_back(room2);

			Room room3(3, 4, Room::DEAD_END, Room::DEAD_END, 1);
			rooms.push_back(room3);

			Room room4(4, Room::DEAD_END, 5, 3, 2);
			rooms.push_back(room4);

			Room room5(5, Room::DEAD_END, Room::STAGE_EXIT, Room::DEAD_END, 4);
			room5.add_monster(Slime(2));
			rooms.push_back(room5);
		}
};

#endif /* TestStage_h */

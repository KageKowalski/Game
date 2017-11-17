#include "Stage.hpp"
#include "Monsters/Slime.hpp"

class TestStage : public Stage{
	public:
		//  Hard-code constructs TestStage.
		TestStage(const string& name);


		//  Singleton Design Pattern.
    	TestStage(TestStage const&) = delete;
    	void operator=(TestStage const&) = delete;
    
    	static TestStage& get()
    	{
			static TestStage instance("TestStage");
			return instance;
    	}
};


TestStage::TestStage(const string& name) : Stage(name) {
	Room room0(0, -1, 1, -1, -1);
	room0.add_monster(Slime(1));
	rooms.push_back(room0);

	Room room1(1, 2, 3, -1, 0);
	room1.add_monster(Slime(1));
	rooms.push_back(room1);

	Room room2(2, -1, 4, 1, -1);
	rooms.push_back(room2);

	Room room3(3, 4, -1, -1, 1);
	rooms.push_back(room3);

	Room room4(4, -1, 5, 3, 2);
	rooms.push_back(room4);

	Room room5(5, -1, -2, -1, 4);
	room5.add_monster(Slime(2));
	rooms.push_back(room5);
}

#ifndef Monster_h
#define Monster_h

#include "Combatant.hpp"

class Monster : public Combatant
{
public:
    Monster(string _name, int _hp, int _str, int _def, int _lck, int _spd, int _gold, int _exp, DiscreteDistribution<Item> _loot = DiscreteDistribution<Item>())
    {
        name = _name;
        hp   = _hp;
        str  = _str;
        def  = _def;
        lck  = _lck;
        spd  = _spd;
        gold = _gold;
        exp  = _exp;
        loot = _loot;
    }

	//  Get or set the id of this Monster.
	//  set_id(int) is called in Room.hpp inside of add_monster(Monster).
	//  Every Monster in a given room has a unique id.
	int get_id()         { return id; }
	void set_id(int _id) { id = _id; }
    
    void level_up(int percent, int& stat, int amount, int secondRoll);
    
    Item get_loot(){ return loot(); }

protected:
    Monster(){}
    DiscreteDistribution<Item> loot;

private:
	int id;	
};
/***********************
    Implementations
 ***********************/

void Monster::level_up(int percent, int& stat, int amount, int secondRoll)
{
    DiscreteDistribution<int> levelChanges;
    DiscreteDistribution<int> second_roll;
    second_roll.add(0, 100-secondRoll);
    second_roll.add(1, secondRoll);
    levelChanges.add(0, 100-percent);
    levelChanges.add(1, percent);
    if(levelChanges())
    {
        stat+=amount;
        if(second_roll())
        {
            level_up(percent, stat, amount, secondRoll-1);
        }
    }
}

#endif /* Monster_h */

#ifndef Monster_h
#define Monster_h

#include "Player.hpp"

class Monster : public Combatant
{
public:
    Monster(string _name, int _hp, int _str, int _def, int _lck, int _spd, int _gold, int _exp, DiscreteDistribution<Item> _loot = DiscreteDistribution<Item>()) : Combatant(_name, _hp, _str, _def, _lck, _spd, _gold, _exp), loot(_loot){}

	//  Get or set the id of this Monster.
	//  set_id(int) is called in Room.hpp inside of add_monster(Monster).
	//  Every Monster in a given room has a unique id.
	int get_id()         { return id; }
	void set_id(int _id) { id = _id; }
    
    void level_up(int percent, int& stat, int amount, int secondRoll);
    Item get_loot(){ return loot(); }
    pair<int, bool> attack_player(Player& mo);
    
    int getLvl() { return level; }

protected:
    Monster() : Combatant(){}
    DiscreteDistribution<Item> loot;
    int level;

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

pair<int, bool> Monster::attack_player(Player& mo)
{
    pair<int, bool> ret;
    if(rollCrit())
    {
        mo.change_cur_hp(round(-((1.5*str-mo.get_def_tot())>0?(1.5*str-mo.get_def_tot()):1)));
        ret.first = round(((1.5*str-mo.get_def_tot())>0?(1.5*str-mo.get_def_tot()):1));
        ret.second = true;
        return ret;
    }
    mo.change_cur_hp(round(-((str-mo.get_def_tot())>0?(str-mo.get_def_tot()):1)));
    ret.first = round((str-mo.get_def_tot())>0?(str-mo.get_def_tot()):1);
    ret.second = false;
    return ret;
}

#endif /* Monster_h */

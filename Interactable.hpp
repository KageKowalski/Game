#ifndef Interactable_h
#define Interactable_h

#include "Monster.hpp"

class Interactable : public Entity
{
public:
    Interactable(string _name, string _desc) : desc(_desc){ name = _name; }
    virtual void interact(){};

	//  Get or set the id of this Interactable.
	//  set_id(int) is called in Room.hpp inside of add_interactable(Interactable).
	//  Every Interactable in a given room has a unique id.
	int get_id()         { return id; }
    void set_id(int _id) { id = _id;  }

protected:
    Interactable(){}
    string desc;

private:
	int id;
};

#endif /* Interactable_h */

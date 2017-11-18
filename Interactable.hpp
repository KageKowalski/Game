#ifndef Interactable_h
#define Interactable_h

#include "Monster.hpp"

class Interactable : public Entity
{
public:
    Interactable(string _name, string _desc) : desc(_desc){ name = _name; }
    virtual void interact(){};
    
protected:
    Interactable(){}
    string desc;
};

#endif /* Interactable_h */

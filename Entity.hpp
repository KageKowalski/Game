#ifndef Entity_h
#define Entity_h

#include <string>
#include <cmath>

#include "IterableDiscreteDistribution.hpp"

using namespace std;

class Entity
{
protected:
    string name;
    
protected:
    Entity(){}
    
    //basic setter and getter for name
    void setName(string x) { name = x;   }
    string getName()       { return name;}
};

#endif /* Entity_h */

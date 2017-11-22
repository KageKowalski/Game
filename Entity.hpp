#ifndef Entity_h
#define Entity_h

#include <string>
#include <cmath>
#include <chrono>

#include "IterableDiscreteDistribution.hpp"

using namespace std;

Random RANDOM_GENERATOR(chrono::high_resolution_clock::now().time_since_epoch().count());

class Entity
{
protected:
    string name;
    
    Entity(){}
    Entity(string _name) : name(_name){}
    
public:
    
    //basic setter and getter for name
    void setName(string x) { name = x;   }
    string getName()       { return name;}
private:

};

#endif /* Entity_h */

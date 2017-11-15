/***************************************************************
 <Josh Seelye>
 <IterableDiscreteDistribution.hpp>
 <Project 3>
 <Inherits the DiscreteDistribution class and adds the iterable functionality>
 ***************************************************************/
#ifndef _ITERABLE_DISCRETE_DISTRIBUTION_GUARD
#define _ITERABLE_DISCRETE_DISTRIBUTION_GUARD

#include <utility>
#include <vector>

#include "DiscreteDistribution.hpp"
#include "Types.h"

//
// Map-based distribution <KEY, WEIGHT>
//     where the weight is cumulative (allowing random number generation)
//     to return the key value
//

template<typename KEY_T>
class IterableDiscreteDistribution : public DiscreteDistribution<KEY_T>
{
  public:

    IterableDiscreteDistribution(){}
    IterableDiscreteDistribution(const IterableDiscreteDistribution<KEY_T>& orig){}
    virtual ~IterableDiscreteDistribution(){}
    
    // Standard Iteration mechanism using vector iterators
    class Iterator
    {
    private:
        typename std::vector<std::pair<KEY_T, WEIGHT_T> >::iterator _current;
        
        // Create an empty Iterator
        Iterator(typename std::vector<std::pair<KEY_T, WEIGHT_T> >::iterator it) : _current(it) { }
        
        
        
    public:
        // Overloaded pre and post increment for iterator
        const Iterator& operator++()           { ++_current;return *this; }
        const Iterator& operator++(int)        { _current++;return *this; }
        
        //overloaded dereference
        KEY_T& operator*()                     { return _current->first; }
        
        //overloaded equals
        Iterator& operator=(const Iterator& it)
        {
            _current = it._current;
            return *this;
        }
        
        //overloaded comparison operators
        bool operator!=(const Iterator& rhs) const { return rhs._current != _current;}
        bool operator==(const Iterator& rhs) const { return rhs._current == _current; }
        
        friend class IterableDiscreteDistribution;
        
        //next function to obtain the next value of the iterator
        const Iterator& next()
        {
            _current++;
            return *this;
        }


    };
    
    //wraps around the begin and end functions of a vector iterator
    Iterator begin()    { return IterableDiscreteDistribution<KEY_T>::_valueToWeightMap.begin(); }
    Iterator end()      { return IterableDiscreteDistribution<KEY_T>::_valueToWeightMap.end();   }
};

#endif

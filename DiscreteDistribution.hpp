/***************************************************************
 <Josh Seelye>
 <DiscreteDistribution.hpp>
 <Project 3>
 <Stores keys with different weights in a vector. Uses weights to create a distribution and roll for a key>
 ***************************************************************/
#ifndef _DISCRETE_DISTRIBUTION_GUARD
#define _DISCRETE_DISTRIBUTION_GUARD

#include <utility>
#include <vector>
#include <iostream>
#include <sstream>
#include <iomanip>

#include "Random.h"

//
// Map-based distribution <KEY, WEIGHT>
//     where the weight is cumulative (allowing random number generation)
//     to return the key value
//
template<typename KEY_T>
class DiscreteDistribution
{
  public:
    DiscreteDistribution();
    DiscreteDistribution(const DiscreteDistribution<KEY_T>& orig);
    const DiscreteDistribution& operator=(const DiscreteDistribution<KEY_T>& orig);

    virtual ~DiscreteDistribution();

    // @param key -- key value for mapping
    // @param weight -- weight of the particular key
    //    If the key is not in the distribution, add it, otherwise,  
     // @throws std::string object for negative weights (when the @param weight is cast to a standard int)
    void add(KEY_T key, unsigned weight);

    // @param key -- key value for mapping
    // @return the weight in the discrete distribution
    unsigned weight(KEY_T key) const;

    // @param key -- key value for mapping
    // @return the probability of the key in w.r.t. the discrete distribution
    double probability(KEY_T key) const;

    //
    // @return Based on the given weights, roll a die to return the resulting key value return a 
    //
    KEY_T operator()() const;

    //
    // toString and overloaded output operator
    //
    std::string toString() const;
    friend std::ostream& operator<<(std::ostream& os, const DiscreteDistribution& dis)
    {
        return os << dis.toString();
    }

  protected:
    // Map of keys to cumulative weights
    std::vector<std::pair<KEY_T, unsigned> > _valueToWeightMap;

    // The random number generator
    Random _rng;
};

template<typename KEY_T>
DiscreteDistribution<KEY_T>::DiscreteDistribution()
{}

template<typename KEY_T>
DiscreteDistribution<KEY_T>::DiscreteDistribution(const DiscreteDistribution<KEY_T>& orig): _valueToWeightMap(orig._valueToWeightMap),_rng(orig._rng)
{}

// Templated Overloaded equals operator
template<typename KEY_T>
const DiscreteDistribution<KEY_T>& DiscreteDistribution<KEY_T>::operator=(const DiscreteDistribution<KEY_T>& orig)
{
    //taking instance variables of the original and reassigning them to this.
    this->_valueToWeightMap = orig._valueToWeightMap;
    this->_rng = orig._rng;
    return *this;
}

template<typename KEY_T>
DiscreteDistribution<KEY_T>::~DiscreteDistribution()
{
    //clearing vector after dying
    _valueToWeightMap.clear();
}

template<typename KEY_T>
void DiscreteDistribution<KEY_T>::add(KEY_T key, unsigned weight)
{
    //A placeholder for the previous weight
    int prev = 0;
    
    //used to check for negatives throws a std::string exception if value is less than 0
    int comp = weight;
    if (comp < 0) throw std::string("Negative");
    for(int i = 0; i < _valueToWeightMap.size(); i++)
    {
        //check if key has already been used
        if( (_valueToWeightMap[i]).first == key)
        {
            //checks if the found key is at position 0. if it is use special case
            if(i == 0)
            {
                prev = (_valueToWeightMap[i]).second;
            }
            else
            {
                prev = (_valueToWeightMap[i]).second - (_valueToWeightMap[i-1]).second;
            }
            //shifts all of the previous weights
            for(int j = i; j < _valueToWeightMap.size(); j++)
            {
                (_valueToWeightMap[j]).second += weight - prev;
            }
            //leave fuction since key has been found
            return;
        }
    }
    //standard add if the key hasn't already been used
    if(_valueToWeightMap.size() == 0)
        _valueToWeightMap.push_back(std::make_pair(key, weight));
    else
        _valueToWeightMap.push_back(std::make_pair(key, _valueToWeightMap.at(_valueToWeightMap.size()-1).second + weight));
}

template<typename KEY_T>
unsigned DiscreteDistribution<KEY_T>::weight(KEY_T key) const
{
    for(int i = 0; i < _valueToWeightMap.size(); i++)
    {
        //check if key is in the vector
        if(_valueToWeightMap.at(i).first == key)
        {
            //checks if the found key is at position 0. if it is use special case
            if(i == 0)
            {
                return _valueToWeightMap.at(i).second;
            }
            else
            {
                return _valueToWeightMap.at(i).second - _valueToWeightMap.at(i-1).second;
            }
        }
    }
    //return 0 for a key that isn't in the vector
    return 0;
}

template<typename KEY_T>
double DiscreteDistribution<KEY_T>::probability(KEY_T key) const
{
    //check for a weight of 0 if found returns 0
    if(_valueToWeightMap[_valueToWeightMap.size()-1].second == 0) { return double(0); }
    
    return double(weight(key))/double(_valueToWeightMap[_valueToWeightMap.size()-1].second);
}

template<typename KEY_T>
KEY_T DiscreteDistribution<KEY_T>::operator()() const
{
    //obtain a random potion to select
    int compare = _rng.nextInt(_valueToWeightMap[_valueToWeightMap.size()-1].second)+1;
    
    for(int i = 0; i < _valueToWeightMap.size()-1;i++)
    {
        //special case for i == 0 where it compares to zero
        if(i==0)
        {
            if(compare > 0 && compare <= _valueToWeightMap[0].second)
            {
                return _valueToWeightMap[0].first;
            }
        }
        else
        {
            if(compare > _valueToWeightMap.at(i).second && compare <= _valueToWeightMap.at(i+1).second)
            {
                return _valueToWeightMap.at(i+1).first;
            }
        }
    }
    return _valueToWeightMap.at(0).first;
}


//
// @return string-based representation of DiscreteDistribution object
//
template<typename KEY_T>
std::string DiscreteDistribution<KEY_T>::toString() const
{
    std::ostringstream oss;

    oss << "\t\t\t\t Cumulative" << std::endl;
    double tot = 0;
    
    //outputs each pairs values
    for(int i = 0; i < _valueToWeightMap.size(); i++)
    {
        oss << _valueToWeightMap.at(i).first << "\t" << (double)weight(_valueToWeightMap.at(i).first) << std::setw(10)<< "\t";
        oss << probability(_valueToWeightMap.at(i).first) << std::setw(10) << (double)_valueToWeightMap.at(i).second << std::setw(10);
        oss << (tot = probability(_valueToWeightMap.at(i).first) + tot) << std::endl;
    }

    return oss.str();
}

#endif

/***************************************************************
 <Josh Seelye>
 <Random.h>
 <Project1>
 <Describe, in general, the code contained.>
 ***************************************************************/

#ifndef _RANDOM_GUARD
#define _RANDOM_GUARD

#include <random>

class Random
{
protected:
    mutable std::default_random_engine _generator;
    mutable std::uniform_int_distribution<int> _uniformIntDistribution;
    mutable std::uniform_real_distribution<double> _uniformRealDistribution;
    mutable std::normal_distribution<double> _normalRealDistribution;
    
public:
    // Creates a new random number generator using an optional long seed.
    Random(long seed = 0);
    
public:
    // Returns the next pseudorandom, uniformly distributed boolean value from this random number generator's sequence.
    bool nextBoolean() const;
    
    // Generates random bytes and places them into a user - supplied byte array
    void nextBytes(char bytes[], int numBytes) const;
    
    // Returns the next pseudorandom, uniformly distributed double value between 0.0 and 1.0 from this random number generator's sequence.
    double nextDouble() const;
    
    // Returns the next pseudorandom, uniformly distributed float value between 0.0 and 1.0 from this random number generator's sequence.
    float nextFloat() const;
    
    // Returns the next pseudorandom, Gaussian("normally") distributed double value with mean 0.0 and standard deviation 1.0 from this random number generator's sequence.
    double nextGaussian() const;
    
    // Returns the next pseudorandom, uniformly distributed int value from this random number generator's sequence.
    int    nextInt() const;
    
    // Returns a pseudorandom, uniformly distributed int value between 0 (inclusive) and the specified value(exclusive), drawn from this random number generator's sequence.
    int    nextInt(int n) const;
    
    // Returns a pseudorandom, uniformly distributed int value between low (inclusive) and high(inclusive), drawn from this random number generator's sequence.
    int    nextInt(int low, int high) const;
    
    // Returns the next pseudorandom, uniformly distributed long value from this random number generator's sequence.
    long nextLong() const;
    
    // Sets the seed of this random number generator using a single long seed.
    void setSeed(long seed = 0);
};

#endif


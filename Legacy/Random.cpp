/***************************************************************
 <Josh Seelye>
 <Random.cpp>
 <Project 1>
 <Class contains code to organize the built in random generator>
 ***************************************************************/

#include <stdio.h>
#include "Random.h"

// Creates a new random number generator using an optional long seed.
Random::Random(long seed)
{
    _generator.seed(seed);
}


// Returns the next pseudorandom, uniformly distributed boolean value from this random number generator's sequence.
bool Random::nextBoolean() const
{
    return _normalRealDistribution(_generator)>0?true:false;
}

// Generates random bytes and places them into a user - supplied byte array
void Random::nextBytes(char bytes[], int numBytes) const
{
    for(int i = 0; i < numBytes; i ++)
    {
        bytes[i] = _uniformIntDistribution(_generator)%255;
    }
        
}

// Returns the next pseudorandom, uniformly distributed double value between 0.0 and 1.0 from this random number generator's sequence.
double Random::nextDouble() const
{
    return _uniformRealDistribution(_generator);
}

// Returns the next pseudorandom, uniformly distributed float value between 0.0 and 1.0 from this random number generator's sequence.
float Random::nextFloat() const
{
    return float(_uniformRealDistribution(_generator));
}

// Returns the next pseudorandom, Gaussian("normally") distributed double value with mean 0.0 and standard deviation 1.0 from this random number generator's sequence.
double Random::nextGaussian() const
{
    return _normalRealDistribution(_generator);
}

// Returns the next pseudorandom, uniformly distributed int value from this random number generator's sequence.
int    Random::nextInt() const
{
    return _uniformIntDistribution(_generator);
}

// Returns a pseudorandom, uniformly distributed int value between 0 (inclusive) and the specified value(exclusive), drawn from this random number generator's sequence.
int    Random::nextInt(int n) const
{
    return (_uniformIntDistribution(_generator)%n);
}

// Returns a pseudorandom, uniformly distributed int value between low (inclusive) and high(inclusive), drawn from this random number generator's sequence.
int    Random::nextInt(int low, int high) const
{
    return (_uniformIntDistribution(_generator)%(high-low+1)+low);
}

// Returns the next pseudorandom, uniformly distributed long value from this random number generator's sequence.
long Random::nextLong() const
{
    return long(_uniformIntDistribution(_generator));
}

// Sets the seed of this random number generator using a single long seed.
void Random::setSeed(long seed)
{
    _generator.seed(seed);
}

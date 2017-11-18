#ifndef SotL_h
#define SotL_h

#include "../../Equipment2.hpp"

class SotL : public Equipment2
{
public:
    SotL(int);
    void increase_lvl();
};

SotL::SotL(int _lvl)
{
    Equipment2("Slayer of the Lifeless", EquipsType::ONE_HANDED);
    for(int i = _lvl; i != -1; i--){increase_lvl();}
}
void SotL::increase_lvl()
{
    level_up(10, str, 30);
    level_up(2, def, 10);
    level_up(15, lck, 10);
    level_up(15, hp, 75);
}

#endif /* SotL_h */

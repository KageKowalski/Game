#ifndef Fists_h
#define Fists_h

#include "../../Equipment.hpp"

class  Fists : public Equipment{
public:
    Fists()
    {
        name = "Fists";
        equipType = EquipType::ONE_HANDED;
    }
};

#endif /* Fists_h */

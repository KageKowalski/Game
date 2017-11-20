#ifndef Fists_h
#define Fists_h

#include "../../Equipment.hpp"

class  Fists : public Equipment{
public:
    Fists()
    {
        Equipment();
        name = "Fists";
        equipType = EquipType::ONE_HANDED;
    }
};

#endif /* Fists_h */

#ifndef Pants_h
#define Pants_h

#include "../../Equipment.hpp"

class  Pants : public Equipment{
public:
    Pants()
    {
        name = "Pants";
        equipType = EquipType::PANTS;
    }
};

#endif /* Pants_h */

#ifndef Shirt_h
#define Shirt_h

#include "../../Equipment.hpp"

class  Shirt : public Equipment{
public:
    Shirt()
    {
        name = "Shirt";
        equipType = EquipType::VEST;
    }
};

#endif /* Shirt_h */

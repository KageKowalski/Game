#ifndef Shoes_h
#define Shoes_h

#include "../../Equipment.hpp"

class  Shoes : public Equipment{
public:
    Shoes()
    {
        name = "Shoes";
        equipType = EquipType::BOOTS;
    }
};

#endif /* Shoes_h */

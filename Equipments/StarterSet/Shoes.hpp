#ifndef Shoes_h
#define Shoes_h

#include "../../Equipment.hpp"

class  Shoes : public Equipment{
public:
    Shoes() : Equipment("Shoes", EquipType::BOOTS)
    {}
};

#endif /* Shoes_h */

#ifndef Hands_h
#define Hands_h

#include "../../Equipment.hpp"

class Hands : public Equipment{
public:
    Hands() : Equipment("Hands", EquipType::GLOVES)
    {}
};

#endif /* Hands_h */

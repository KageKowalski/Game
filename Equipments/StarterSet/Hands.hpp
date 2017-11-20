#ifndef Hands_h
#define Hands_h

#include "../../Equipment.hpp"

class Hands : public Equipment{
public:
    Hands()
    {
        Equipment();
        name = "Hands";
        equipType = EquipType::GLOVES;
    }
};

#endif /* Hands_h */

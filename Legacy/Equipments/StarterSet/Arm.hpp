#ifndef Arm_h
#define Arm_h

#include "../../Equipment.hpp"

class  Arm : public Equipment{
public:
    Arm() : Equipment("Arm", EquipType::SHIELD)
    {}
};

#endif /* Arm_h */

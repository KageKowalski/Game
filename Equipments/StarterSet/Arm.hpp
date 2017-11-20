#ifndef Arm_h
#define Arm_h

#include "../../Equipment.hpp"

class  Arm : public Equipment{
public:
    Arm()
    {
        name = "Arm";
        equipType = EquipType::SHIELD;
    }
};

#endif /* Arm_h */

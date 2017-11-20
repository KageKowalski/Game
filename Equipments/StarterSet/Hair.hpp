#ifndef Hair_h
#define Hair_h

#include "../../Equipment.hpp"

class  Hair : public Equipment{
public:
    Hair()
    {
        Equipment();
        name = "Hair";
        equipType = EquipType::HELMET;
    }
};

#endif /* Hair_h */

#ifndef Nothing_h
#define Nothing_h

#include "../../Equipment.hpp"

class Nothing : public Equipment{
public:
    Nothing()
    {
        Equipment();
        name = "Nothing";
        equipType = EquipType::TWO_HANDED;
    }
};

#endif /* Nothing_h */

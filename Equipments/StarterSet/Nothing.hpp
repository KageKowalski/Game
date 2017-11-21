#ifndef Nothing_h
#define Nothing_h

#include "../../Equipment.hpp"

class Nothing : public Equipment{
public:
    Nothing() : Equipment("Nothing", EquipType::TWO_HANDED)
    {}
};

#endif /* Nothing_h */

#ifndef BuyableEquipment_h
#define BuyableEquipment_h

#include "Equipment.hpp"

class BuyableEquipment : public Equipment
{
//instance Variables
private:
    int price;
    Equipment eq;
    
//public functions
public:
    int get_price();
    Equipment& get_item();

//constructors
public:
    BuyableEquipment(){}
    BuyableEquipment(const Equipment& _eq, int _price) : price(_price), eq(_eq){}
    
};

int BuyableEquipment::get_price()       { return price; }
Equipment& BuyableEquipment::get_item() { return eq;    }


#endif /* Buyable_h */


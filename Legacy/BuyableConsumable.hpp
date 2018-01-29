#ifndef BuyableConsumable_h
#define BuyableConsumable_h

#include "Consumable.hpp"

class BuyableConsumable : public Consumable
{
    //instance Variables
private:
    int price;
    Consumable con;
    
    //public functions
public:
    int get_price();
    Consumable& get_item();
    
    //constructors
public:
    BuyableConsumable(){}
    BuyableConsumable(const Consumable& _con, int _price) : price(_price), con(_con){}
    
};

int BuyableConsumable::get_price()       { return price; }
Consumable& BuyableConsumable::get_item() { return con;    }

#endif /* BuyableConsumable_h */

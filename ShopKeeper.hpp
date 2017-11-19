
#ifndef ShopKeeper_h
#define ShopKeeper_h

#include "Interactable.hpp"
#include "Buyable.hpp"

class ShopKeeper : public Interactable
{
//instance variables
private:
    vector<Buyable> forsale;
    int pos;
    
//public Functions
public:
    void interact();
    const Buyable& get_current();
    const Buyable& next();
    const Buyable& prev();
    
    
public:
    ShopKeeper(vector<Buyable> _forsale, string _name = "Shop Keeper", string _desc = "An old man that has ran this place for years.")
    {
        forsale = _forsale;
        name    = _name;
        desc    = _desc;
        pos = 0;
    }
};

const Buyable& ShopKeeper::get_current()
{
    return forsale[pos];
}

const Buyable& ShopKeeper::next()
{
    if(forsale.size() == 1)          {          }
    else if(pos == forsale.size()-1) { pos = 0; }
    else                             { pos++;   }
    return forsale[pos];
}

const Buyable& ShopKeeper::prev()
{
    if(forsale.size() == 1)          {          }
    else if(pos == 0) { pos = forsale.size()-1; }
    else                             { pos--;   }
    return forsale[pos];
}


#endif /* ShopKeeper_h */

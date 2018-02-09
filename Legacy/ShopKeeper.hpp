#ifndef ShopKeeper_h
#define ShopKeeper_h

#include "Interactable.hpp"
#include "BuyableEquipment.hpp"
#include "BuyableConsumable.hpp"
#include "Player.hpp"

class ShopKeeper : public Interactable
{
//instance variables
private:
    pair<bool, Equipment>       toRetEq;
    pair<bool, Consumable>      toRetCon;
    vector<BuyableEquipment>    forsaleEq;
    vector<BuyableConsumable>   forsaleCon;
    int posEq;
    int posCon;
    
//public Functions
public:
    
    BuyableEquipment&           get_current_eq();
    BuyableEquipment&           next_eq();
    BuyableEquipment&           prev_eq();
    void add(BuyableEquipment&  item);
    
    BuyableConsumable&          get_current_con();
    BuyableConsumable&          next_con();
    BuyableConsumable&          prev_con();
    void add(BuyableConsumable& item);
    
    //returns true if item was bought based on player gold, second item will be empty if first is false;
    pair<bool, Consumable>&     buy_con();
    pair<bool, Equipment>&      buy_eq();
    
    //check type of shopkeeper could be Equipment, Consumable, or both
    bool empty_eq()                   { return forsaleEq.empty();  }
    bool empty_con()                  { return forsaleCon.empty(); }

    //gets buyable item to output to user
    BuyableEquipment& interact_eq()   { return get_current_eq();  }
    BuyableConsumable& interact_con() { return get_current_con(); }
    
public:
    //Different Overloaded Constructors for all types of shopkeeper
    ShopKeeper(string _name = "Shop Keeper", string _desc = "An old man that has ran this place for years.");
    ShopKeeper(vector<BuyableEquipment>& _forsaleEq, string _name = "Shop Keeper", string _desc = "Default Eq");
    ShopKeeper(vector<BuyableConsumable>& _forsaleCon, string _name = "Shop Keeper", string _desc = "Default Con");
    ShopKeeper(vector<BuyableEquipment> _forsaleEq, vector<BuyableConsumable>& _forsaleCon, string _name = "Shop Keeper", string _desc = "Default Eq and Con");
    
};


/***********************
      Constructors
 ***********************/
ShopKeeper::ShopKeeper(string _name, string _desc)
{
    name    = _name;
    desc    = _desc;
    posEq = 0;
    posCon = 0;
}
ShopKeeper::ShopKeeper(vector<BuyableEquipment>& _forsaleEq, string _name, string _desc)
{
    forsaleEq = _forsaleEq;
    forsaleEq.shrink_to_fit();
    name    = _name;
    desc    = _desc;
    posEq = 0;
    posCon = 0;
}
ShopKeeper::ShopKeeper(vector<BuyableConsumable>& _forsaleCon, string _name, string _desc)
{
    forsaleCon = _forsaleCon;
    forsaleCon.shrink_to_fit();
    name    = _name;
    desc    = _desc;
    posEq = 0;
    posCon = 0;
}

ShopKeeper::ShopKeeper(vector<BuyableEquipment> _forsaleEq, vector<BuyableConsumable>& _forsaleCon, string _name, string _desc)
{
    forsaleEq = _forsaleEq;
    forsaleEq.shrink_to_fit();
    forsaleCon = _forsaleCon;
    forsaleCon.shrink_to_fit();
    name    = _name;
    desc    = _desc;
    posEq = 0;
    posCon = 0;
}


/***********************
   Equipment Functions
 ***********************/
void ShopKeeper::add(BuyableEquipment& item)
{
    forsaleEq.resize(forsaleEq.size()+1);
    forsaleEq.push_back(item);
}

BuyableEquipment& ShopKeeper::get_current_eq()
{
    return forsaleEq[posEq];
}

BuyableEquipment& ShopKeeper::next_eq()
{
    if(forsaleEq.size() == 1)          {          }
    else if(posEq == forsaleEq.size()-1) { posEq = 0; }
    else                             { posEq++;   }
    return forsaleEq[posEq];
}

BuyableEquipment& ShopKeeper::prev_eq()
{
    if(forsaleEq.size() == 1)          {          }
    else if(posEq == 0) { posEq = forsaleEq.size()-1; }
    else                             { posEq--;   }
    return forsaleEq[posEq];
}

pair<bool, Equipment>& ShopKeeper::buy_eq()
{
    if(Player::get().getGold()<get_current_eq().get_price())
    {
        toRetEq.first = false;
        toRetEq.second = Equipment();
        return toRetEq;
    }
    Player::get().setGold(-(get_current_eq().get_price()));
    toRetEq.first = true;
    toRetEq.second = get_current_eq().get_item();
    forsaleEq.erase((forsaleEq.begin()+posEq));
    return toRetEq;
}



/***********************
  Consumable Functions
 ***********************/
void ShopKeeper::add(BuyableConsumable& item)
{
    forsaleCon.resize(forsaleCon.size()+1);
    forsaleCon.push_back(item);
}

BuyableConsumable& ShopKeeper::get_current_con()
{
    return forsaleCon[posCon];
}

BuyableConsumable& ShopKeeper::next_con()
{
    if(forsaleCon.size() == 1)          {          }
    else if(posCon == forsaleCon.size()-1) { posCon = 0; }
    else                             { posCon++;   }
    return forsaleCon[posCon];
}

BuyableConsumable& ShopKeeper::prev_con()
{
    if(forsaleCon.size() == 1)          {          }
    else if(posCon == 0) { posCon = forsaleCon.size()-1; }
    else                             { posCon--;   }
    return forsaleCon[posCon];
}

pair<bool, Consumable>& ShopKeeper::buy_con()
{
    if(Player::get().getGold()<get_current_con().get_price())
    {
        toRetCon.first = false;
        toRetCon.second = Consumable();
        return toRetCon;
    }
    Player::get().setGold(-(get_current_con().get_price()));
    toRetCon.first = true;
    toRetCon.second = get_current_con().get_item();
    forsaleCon.erase((forsaleCon.begin()+posCon));
    return toRetCon;
}

#endif /* ShopKeeper_h */

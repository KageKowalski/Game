
#ifndef StatModifiers_h
#define StatModifiers_h

#include "Item.hpp"


class Equipment : public Item
{
private:
    int hpMod;
    int strMod;
    int defMod;
    int lckMod;
    int spdMod;
    bool xpBoost;
public:
    Equipment(string _name, int _hpMod, int _strMod, int _defMod, int _lckMod, int _spdMod, bool _xpBoost)
    {
        name    = _name;
        hpMod   = _hpMod;
        strMod  = _strMod;
        defMod  = _defMod;
        lckMod  = _lckMod;
        spdMod  = _spdMod;
        xpBoost = _xpBoost;
    }
    
    string getName()    { return name;    }
    
    int getHpMod()      { return hpMod;   }
    
    int getStrMod()     { return strMod;  }
    
    int getDefMod()     { return defMod;  }
    
    int getLckMod()     { return lckMod;  }
    
    bool getXpBoost()   { return xpBoost; }
    
    bool operator==(const Equipment& rhs)
    {
        if((name == rhs.name) && (strMod == rhs.strMod) && (defMod == rhs.defMod) && (lckMod == rhs.lckMod) && (spdMod == rhs.spdMod) && (xpBoost == rhs.xpBoost))
        {
            return true;
        }
        return false;
    }
    
};

#endif /* StatModifiers_h */

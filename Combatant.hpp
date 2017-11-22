#ifndef Combatant_h
#define Combatant_h

#include "Entity.hpp"
#include "Equipment.hpp"
#include "Player.hpp"

class Combatant : public Entity
{
public:
    int getExp() { return exp;     }
	int getHp()  { return hp;      }
	int getStr() { return str;     }
	int getDef() { return def;     }
	int getLck() { return lck;     }
	int getSpd() { return spd;     }
    int getGold(){ return gold;    }

    virtual void setHp(int x)  { hp += x;  }
	virtual void setStr(int x) { str += x; }
	virtual void setDef(int x) { def += x; }
	virtual void setLck(int x) { lck += x; }
	virtual void setSpd(int x) { spd += x; }
    virtual void setGold(int x){ gold +=x; }
    
    bool rollDodge()   { updateDodge(); return dodge(); }
    virtual bool isDead()      { return getHp()<=0;             }
    
    double getDodgePercent()
    {
        updateDodge();
        return dodge.probability(1)*100;
    }
    double getCritPercent()
    {
        updateCrit();
        return crit.probability(1)*100;
    }
    
protected:
    int hp;
    int spd;
    int str;
    int def;
    int lck;
    int gold;
    int exp;

    //discrete distributions only returns 1 or 0 based on if you crit/dodged
    DiscreteDistribution<bool> crit;
    DiscreteDistribution<bool> dodge;
    
    bool rollCrit()    { updateCrit();  return crit();  }

    
    void updateDodge()
    {
        dodge.add(false, 165-(int)(lck*.5)-spd);
        dodge.add(true, lck+spd);
    }
    
    void updateCrit()
    {
        crit.add(false, 100-lck);
        crit.add(true, lck);
    }
    
    Combatant(string _name, int _hp, int _str, int _def, int _lck, int _spd, int _gold, int _exp) : Entity(_name), hp(_hp), spd(_spd), str(_str), def(_def), lck(_lck), gold(_gold), exp(_exp){}
    
    Combatant(){}
    
};

#endif /* Combatant_h */

#ifndef Combatant_h
#define Combatant_h

#include "Entity.hpp"
#include "Equipment.hpp"

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

    void setHp(int x)  { hp += x;  }
	void setStr(int x) { str += x; }
	void setDef(int x) { def += x; }
	void setLck(int x) { lck += x; }
	void setSpd(int x) { spd += x; }
    void setGold(int x){ gold +=x; }
    
    bool rollDodge()   { updateDodge(); return dodge(); }
    bool rollCrit()    { updateCrit();  return crit();  }
    bool isDead()      { return getHp()<=0;             }
    
    
    virtual pair<int, bool> attack(Combatant& mo)
    {
        pair<int, bool> ret;
        if(rollCrit())
        {
            mo.setHp(round(-((1.5*str-mo.getDef())>0?(1.5*str-mo.getDef()):1)));
            ret.first = round(((1.5*str-mo.getDef())>0?(1.5*str-mo.getDef()):1));
            ret.second = true;
            return ret;
        }
        mo.setHp(round(-((str-mo.getDef())>0?(str-mo.getDef()):1)));
        ret.first = round((str-mo.getDef())>0?(str-mo.getDef()):1);
        ret.second = false;
        return ret;
    }
    
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

    
    void updateDodge()
    {
        dodge.add(false, 230-lck-spd);
        dodge.add(true, lck+spd);
    }
    
    void updateCrit()
    {
        crit.add(false, 100-lck);
        crit.add(true, lck);
    }
    
};

#endif /* Combatant_h */

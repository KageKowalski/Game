//
//  Character.hpp
//  GameFirstDraft
//
//  Created by Joshua Seelye on 11/13/17.
//  Copyright © 2017 Josh Seelye. All rights reserved.
//

#ifndef Character_h
#define Character_h

#include "Entity.hpp"
#include "Item.hpp"

class Combatant : public Entity
{
public:
    int getExp(){ return exp;      }
    
	int getHp() { return hp;       }

	int getStr() { return str;     }

	int getDef() { return def;     }

	int getLck() { return lck;     }

	int getSpd() { return spd;     }
    
    int getGold(){ return gold;    }

    void setHp(int x)  { hp += x;  if(hp <= 0) death(); }

	void setStr(int x) { str += x; }

	void setDef(int x) { def += x; }

	void setLck(int x) { lck += x; }

	void setSpd(int x) { spd += x; }
    
    void setGold(int x){ gold +=x; }
    
    bool rollDodge()   { updateDodge(); return dodge(); }
    
    virtual int attack(Combatant& mo)
    {
        mo.setHp(-((str-mo.getDef())>0?(str-mo.getDef()):1));
        return (str-mo.getDef())>0?(str-mo.getDef()):1;
    }
    
    virtual Item death() = 0;
    
    double getDodgePercent()
    {
        updateDodge();
        return dodge.probability(1)*100;
    }
    
protected:
    int hp;
    int spd;
    int str;
    int def;
    int lck;
    int gold;
    int exp;
    DiscreteDistribution<bool> dodge;
    
    void updateDodge()
    {
        dodge.add(false, 230-lck-spd);
        dodge.add(true, lck+spd);
    }
    
};

#endif /* Character_h */

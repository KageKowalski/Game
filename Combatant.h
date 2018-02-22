#ifndef Combatant_h
#define Combatant_h

#include "Entity.h"

class Combatant : public Entity
{
protected:
    // combatant variables for vitality, strength, defence, luck, speed, attack speed, gold, and exp
    int    _vit;
    int    _str;
    int    _def;
    int    _lck;
    int    _spd;
    int    _tme;
    int    _gld;
    int    _exp;
    
    int _curVit;
    int _curStr;
    int _curDef;
    int _curLck;
    int _curSpd;
    int _curTme;
    
public:
    
    //constructors
    Combatant() = delete;
    Combatant(int vit, int str, int def, int lck, int spd, int tme, int gld, int exp);
    
};

#endif

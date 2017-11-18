
#ifndef SerratedDirk_h
#define SerratedDirk_h

#include "../../Equipment.hpp"

//  Stat increase per level: 1.09

class SerratedDirk : public Equipment{
public:
    SerratedDirk(int);
    void level_up();
};

SerratedDirk::SerratedDirk(int _lvl){
    Equipment("Serrated Dirk", EquipType::ONE_HANDED);
    
    levelChanges.add(0, 40);
    levelChanges.add(1, 8);
    levelChanges.add(2, 12);
    levelChanges.add(3, 5);
    levelChanges.add(4, 12);
    levelChanges.add(5, 10);
    levelChanges.add(6, 13);
    
    for(int i = 0; i < _lvl; i++) level_up();
}

void SerratedDirk::level_up(){
    int roll = levelChanges();
    
    switch(roll){
        case 1:
            hp++;
            break;
        case 2:
            str+=3;
            break;
        case 3:
            def++;
            break;
        case 4:
            spd+=2;
            break;
        case 5:
            lck++;
            break;
        case 6:
            str+=2;
    }
    
    lvl++;
}


#endif /* SerratedDirk_h */

//poop
#ifndef RogueLeggings_h
#define RogueLeggings_h

#include "../../Equipment.hpp"

//  Stat increase per level: 0.93

class RogueLeggings : public Equipment{
public:
    RogueLeggings(int);
    void level_up();
};

RogueLeggings::RogueLeggings(int _lvl){
    Equipment("Rogue Leggings", EquipType::PANTS);
    
    levelChanges.add(0, 35);
    levelChanges.add(1, 11);
    levelChanges.add(2, 15);
    levelChanges.add(3, 9);
    levelChanges.add(4, 12);
    levelChanges.add(5, 15);
    levelChanges.add(6, 3);
    
    for(int i = 0; i < _lvl; i++) level_up();
}

void RogueLeggings::level_up(){
    int roll = levelChanges();
    
    switch(roll){
        case 1:
            def++;
            break;
        case 2:
            spd+=2;
            break;
        case 3:
            spd+=3;
            break;
        case 4:
            lck++;
            break;
        case 5:
            hp+=2;
            break;
        case 6:
            str++;
    }
    
    lvl++;
}


#endif /* RogueLeggings_h */

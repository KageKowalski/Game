// Klayton Kowalski

#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"

class Player : public Character {
private:
    Player();
public:
    Player(Player const&)        = delete;
    void operator=(Player const&)  = delete;
    
    static Player& get()
    {
        static Player instance;
        return        instance;
    }
	virtual ~Player();

};

#endif

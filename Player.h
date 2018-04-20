// Klayton Kowalski

#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"

class Player : public Character {
private:
    Player();
    
    int      _currStamina;
    int      _maxStamina;
    sf::Time _elapsedTimeDecrement;
    sf::Time _elapsedTimeIncrement;
public:
    int  getStamina() const;
    bool decrementStamina();
    bool incrementStamina();
    void setStamina(int value);
    
    void update(sf::Time deltaTime) override;
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

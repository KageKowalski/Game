#include "System.hpp"
#include "Monster.hpp"

#define PLAYER Player::get()

int main()
{
//    System system;
//    int retCode = system.run();
//    system.shutDown();
//    return retCode;
    
    
    
    Monster zombie = Monster(4,9,1,1,1,1,1);
    zombie.attack(PLAYER);
    PLAYER.attack(zombie);
    cout << zombie.getHp() << endl;
    cout << PLAYER.getHp() << endl;

}

#include "System.hpp"
#include "Monster.hpp"

#define PLAYER Player::get()

int main()
{
//    System system;
//    int retCode = system.run();
//    system.shutDown();
//    return retCode;
    PLAYER.setLck(50);
    
    for (int i = 0; i != 100; i++){
    Monster zombie = Monster(4,9,0,1,1,1,1);
    zombie.attack(PLAYER);
    PLAYER.attack(zombie);
    cout << zombie.getHp() << endl;

    }

}

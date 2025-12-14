#include "Game.h"
#include <iostream>

void Game::start() {
    Player p(50, 10);
    Enemy e(30, 5);

    std::cout << "Battle simulation..." << std::endl;
    e.takeDamage(p.getAttackPower());
    std::cout << "Enemy HP after hit: " << e.getHealth() << std::endl;

}

#include "Game.h"
#include "FileManager.h"
#include <iostream>

void Game::start() {
    Player p(50, 10);
    Enemy e(30, 5);

    std::cout << "Battle simulation..." << std::endl;
    e.takeDamage(p.getAttackPower());
    std::cout << "Enemy HP after hit: " << e.getHealth() << std::endl;


	// Load enemies from file
    auto enemies = FileManager::loadEnemies("enemies.txt");

    std::cout << "Loaded enemies:\n";
    for (const auto& e : enemies) {
        std::cout << e << std::endl;
    }

    FileManager::saveReport("report.txt", "Test OKKKK");
}

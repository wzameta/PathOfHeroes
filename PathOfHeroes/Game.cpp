#include "Game.h"
#include "FileManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

struct EnemyRow {
    std::string name;
    int hp = 0;
    int ap = 0;
};

static std::vector<EnemyRow> loadEnemiesSimple(const std::string& path) {
    std::ifstream file(path);
    std::vector<EnemyRow> out;

    if (!file.is_open()) {
        std::cout << "[ERROR] Cannot open file: " << path << "\n";
        return out;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        EnemyRow e;
        if (iss >> e.name >> e.hp >> e.ap) {
            out.push_back(e);
        }
    }
    return out;
}

static void saveReportSimple(const std::string& path, const std::string& text) {
    std::ofstream file(path);
    file << text;
}

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

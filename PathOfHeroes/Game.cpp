#include "Game.h"
#include "Enemy.h"
#include "FileManager.h"
#include "AsciiArt.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>


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
    std::srand((unsigned)std::time(nullptr));
    std::cout << "Starting game...\n";
    
   
    // Wczytanie przeciwników 
    auto enemies = loadEnemiesSimple("enemies.txt");

    if (enemies.empty()) {
        std::cout << "No enemies loaded. Check Resource Files/enemies.txt\n";
        return;
    }

    int idx = std::rand() % enemies.size();
    auto& e = enemies[idx];
    EnemyType type;

    if (e.name == "Goblin") type = EnemyType::Goblin;
    else if (e.name == "Orc") type = EnemyType::Orc;
    else if (e.name == "Skeleton") type = EnemyType::Skeleton;
    else type = EnemyType::Goblin; // fallback

    Enemy enemy(e.hp, e.ap, type);

    // Utwórz Player
    Player player(50, 10);

    int level = player.getLevel();

    enemy.setHealth(enemy.getHealth() + level * 10);
    enemy.setAttackPower(enemy.getAttackPower() + level * 2);

    std::cout << "Battle begins: Player vs " << enemies[0].name << "\n";
    std::cout << AsciiArt::load(enemy.getAsciiArtPath()) << std::endl;

    std::cout << "Enemy chosen: " << e.name
        << " (HP " << enemy.getHealth()
        << ", AP " << enemy.getAttackPower()
        << ", Level " << player.getLevel() << ")\n";


    // walka turowa
    int turn = 1;
    while (player.isAlive() && enemy.isAlive()) {
        std::cout << "\n--- Turn " << turn << " ---\n";

        std::cout << "Player attacks!\n";
        player.attack(&enemy);
        std::cout << "Enemy HP: " << enemy.getHealth() << "\n";

        if (!enemy.isAlive()) break;

        std::cout << "Enemy attacks!\n";
        enemy.attack(&player);
        std::cout << "Player HP: " << player.getHealth() << "\n";

        turn++;
    }

    // wynik, raport
    std::string winner = player.isAlive() ? "Player" : e.name;

    std::string report;
    report += "=== RPG REPORT ===\n";
    report += "Enemy: " + e.name + "\n";
    report += "Winner: " + winner + "\n";
    report += "Turns: " + std::to_string(turn) + "\n";
    report += "Player HP: " + std::to_string(player.getHealth()) + "\n";
    report += "Enemy HP: " + std::to_string(enemy.getHealth()) + "\n";
    report += "Player level: " + std::to_string(player.getLevel()) + "\n";

    saveReportSimple("report.txt", report);

    std::cout << "\nBattle finished! Winner: " << winner << "\n";
    std::cout << "Report saved to report.txt\n";
}

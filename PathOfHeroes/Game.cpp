#include "Game.h"
#include "AsciiArt.h"
#include "Enemy.h"
#include "FileManager.h"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>

struct EnemyRow
{
    std::string name;
    int hp = 0;
    int ap = 0;
};

static int randRange(int a, int b)
{ // inclusive
    return a + (std::rand() % (b - a + 1));
}

static EnemyType typeFromName(const std::string &name)
{
    if (name == "Goblin")
        return EnemyType::Goblin;
    if (name == "Orc")
        return EnemyType::Orc;
    if (name == "Skeleton")
        return EnemyType::Skeleton;
    return EnemyType::Goblin;
}

// losowe staty + wzrost po liczbie wygranych
static void rollBalancedStats(const EnemyRow &e, int winsSoFar, int &outHp, int &outAp)
{
    outHp = e.hp + randRange(-3, 3) + winsSoFar * 2;   // HP roœnie
    outAp = e.ap + randRange(-1, 2) + (winsSoFar / 2); // AP roœnie

    if (outHp < 1)
        outHp = 1;
    if (outAp < 1)
        outAp = 1;
}

void Game::start()
{
    std::srand((unsigned)std::time(nullptr));

    const int WIN_CONDITION = 5;
    int wins = 0;

    // START MENU
    while (true)
    {
        std::cout << "=== PATH OF HEROES ===\n";
        std::cout << "1) Wyrusz w droge\n";
        std::cout << "2) Zakoncz\n> ";

        int startChoice;
        if (!(std::cin >> startChoice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Niepoprawny wybor. Wpisz 1 lub 2.\n";
            continue;
        }
        if (startChoice == 2)
            return;
        if (startChoice != 1) {
            std::cout << "Niepoprawny wybor. Wpisz 1 lub 2.\n";
            continue;
        }

        // start gry
        Player player(100, 15);

        // WCZYTAJ LISTE PRZECIWNIKOW (reuse FileManager - single place for file IO)
        auto rawLines = FileManager::loadEnemies("enemies.txt");
        std::vector<EnemyRow> enemies;
        for (const auto &line : rawLines)
        {
            std::istringstream iss(line);
            EnemyRow e;
            if (iss >> e.name >> e.hp >> e.ap)
            {
                enemies.push_back(e);
            }
        }

        if (enemies.empty())
        {
            std::cout << "No enemies loaded. Check enemies.txt\n";
            return;
        }

        // PETLA DROGI
        while (player.isAlive() && wins < WIN_CONDITION)
        {
            // LOSUJ SPOTKANIE
            int idx = std::rand() % enemies.size();
            auto &e = enemies[idx];

            EnemyType type = typeFromName(e.name);

            int hp, ap;
            rollBalancedStats(e, wins, hp, ap);

            Enemy enemy(hp, ap, type);

            std::cout << "\n--- SPOTKANIE ---\n";
            std::cout << "Spotykasz: " << e.name << " (HP " << enemy.getHealth() << ", AP " << enemy.getAttackPower()
                      << ")\n";
            std::cout << AsciiArt::load(enemy.getAsciiArtPath()) << std::endl;

            // WALKA / UCIECZKA
            bool escaped = false;
            int turn = 1;

            while (player.isAlive() && enemy.isAlive())
            {
                std::cout << "\n--- Tura " << turn << " ---\n";
                std::cout << "1) Atak\n2) Ucieczka\n> ";

                int choice;
                if (!(std::cin >> choice)) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Niepoprawny wybor. Wpisz 1 lub 2.\n";
                    continue;
                }

                if (choice == 1) {
                    // ATAK
                    std::cout << "Player attacks!\n";
                    player.attack(&enemy);
                    std::cout << "Enemy HP: " << enemy.getHealth() << "\n";
                    if (!enemy.isAlive())
                        break;

                    std::cout << "Enemy attacks!\n";
                    enemy.attack(&player);
                    std::cout << "Player HP: " << player.getHealth() << "\n";
                    turn++;
                }
                else if (choice == 2) {
                    // UCIECZKA
                    if (std::rand() % 2 == 0) {
                        std::cout << "Ucieczka udana!\n";
                        escaped = true;
                        break;
                    }
                    else {
                        std::cout << "Ucieczka nieudana! Przeciwnik atakuje.\n";
                        enemy.attack(&player);
                        std::cout << "Player HP: " << player.getHealth() << "\n";
                        turn++;
                    }
                }
                else {
                    std::cout << "Niepoprawny wybor. Wpisz 1 lub 2.\n";
                    continue; 
                }
            }

            // KONIEC SPOTKANIA - WARUNKI
            if (!player.isAlive())
            {
                std::string report;
                report += "=== RPG REPORT ===\n";
                report += "Result: Defeat\n";
                report += "Wins: " + std::to_string(wins) + "/" + std::to_string(WIN_CONDITION) + "\n";
                report += "Last enemy: " + e.name + "\n";
                report += "Turns: " + std::to_string(turn) + "\n";
                report += "Player HP: " + std::to_string(player.getHealth()) + "\n";
                report += "Enemy HP: " + std::to_string(enemy.getHealth()) + "\n";
                FileManager::saveReport("report.txt", report);

                std::cout << "\nZgineles. Koniec gry.\n";
                std::cout << "Report saved to report.txt\n";
                return;
            }

            if (!escaped && !enemy.isAlive())
            {
                wins++;
                std::cout << "\nWygrales walke! Wygrane: " << wins << "/" << WIN_CONDITION << "\n";

                std::string report;
                report += "=== RPG REPORT ===\n";
                report += "Enemy: " + e.name + "\n";
                report += "Winner: Player\n";
                report += "Wins: " + std::to_string(wins) + "/" + std::to_string(WIN_CONDITION) + "\n";
                report += "Turns: " + std::to_string(turn) + "\n";
                report += "Player HP: " + std::to_string(player.getHealth()) + "\n";
                report += "Enemy HP: " + std::to_string(enemy.getHealth()) + "\n";
                FileManager::saveReport("report.txt", report);
            }

            // WYGRANA GRY (5 walk)
            if (wins >= WIN_CONDITION)
            {
                std::string report;
                report += "=== RPG REPORT ===\n";
                report += "Result: Victory (5 wins)\n";
                report += "Wins: " + std::to_string(wins) + "/" + std::to_string(WIN_CONDITION) + "\n";
                report += "Player HP: " + std::to_string(player.getHealth()) + "\n";
                FileManager::saveReport("report.txt", report);

                std::cout << "\nGRATULACJE! Wygrales gre (5 wygranych).\n";
                std::cout << "Report saved to report.txt\n";
                return;
            }

            // MENU PO SPOTKANIU (po walce lub ucieczce)
            while (true)
            {
                std::cout << "\n1) Wyrusz dalej\n2) Zakoncz droge\n> ";

                int after;
                if (!(std::cin >> after)) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Niepoprawny wybor. Wpisz 1 lub 2.\n";
                    continue;
                }

                if (after == 1)
                    break;
                if (after == 2)
                {
                    std::string report;
                    report += "=== RPG REPORT ===\n";
                    report += "Result: Abandoned (player ended the journey)\n";
                    report += "Wins: " + std::to_string(wins) + "/" + std::to_string(WIN_CONDITION) + "\n";
                    report += "Player HP: " + std::to_string(player.getHealth()) + "\n";
                    FileManager::saveReport("report.txt", report);

                    std::cout << "\nZakonczyles droge.\n";
                    std::cout << "Report saved to report.txt\n";
                    return;
                }

                std::cout << "Niepoprawny wybor. Wpisz 1 lub 2.\n";
            }
        }
    }
}

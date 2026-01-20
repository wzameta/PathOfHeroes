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

struct EnemyRow
{
    std::string name;
    int hp = 0;
    int ap = 0;
};

static std::vector<EnemyRow> loadEnemiesSimple(const std::string &path)
{
    std::ifstream file(path);
    std::vector<EnemyRow> out;

    if (!file.is_open())
    {
        std::cout << "[ERROR] Cannot open file: " << path << "\n";
        return out;
    }

    std::string line; //zamiana na liste

	//odczyt linii pliku - zwracanie wektora out (pusty jesli linia ró¿na od spodziewanych danych)
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        EnemyRow e;
        if (iss >> e.name >> e.hp >> e.ap)
        {
            out.push_back(e);
        }
    }
    return out;
}
// losowanie liczby z przedzialu [a, b]
static int randRange(int a, int b)
{ 
    return a + (std::rand() % (b - a + 1));
}

// zamiana nazwy przeciwnika z pliku na typ Enemy
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
    outAp = e.ap + randRange(-2, 2) + (winsSoFar / 2); // AP roœnie

    if (outHp < 1)
        outHp = 1;
    if (outAp < 1)
        outAp = 1;
}

// otwarcie pliku do zapisu
static void saveReportSimple(const std::string &path, const std::string &text)
{
    std::ofstream file(path);
    file << text;
}

void Game::start()
{
    //przygotowanie generatora losowosci
    std::srand((unsigned)std::time(nullptr));

	// warunki wygranej
    const int WIN_CONDITION = 5;
    int wins = 0;

	// petla calej gry
    while (true)
    {
        std::cout << "=== PATH OF HEROES ===\n";
        std::cout << "1) Wyrusz w droge\n";
        std::cout << "2) Zakoncz\n> ";

        int startChoice;
        std::cin >> startChoice;

        if (startChoice == 2)
            return;
        if (startChoice != 1)
            continue;




		// statystki gracza
        Player player(100, 15);

        // wczytywanie przeciwnikow do gry
        auto enemies = loadEnemiesSimple("enemies.txt");
        if (enemies.empty())
        {
            std::cout << "No enemies loaded. Check enemies.txt\n";
            return;
        }

        // petla spotkan
        while (player.isAlive() && wins < WIN_CONDITION)
        {
			// losowy wrog - na podstawie ilosci wrogow w pliku
            int idx = std::rand() % enemies.size();
            auto &e = enemies[idx];

            EnemyType type = typeFromName(e.name);

            int hp, ap;
            rollBalancedStats(e, wins, hp, ap);

			//wyswietlenie przeciwnika z "losowymi" danymi
            Enemy enemy(hp, ap, type); 

            std::cout << "\n--- SPOTKANIE ---\n";
            std::cout << "Spotykasz: " << e.name << " (HP " << enemy.getHealth() << ", AP " << enemy.getAttackPower()
                      << ")\n";
            std::cout << AsciiArt::load(enemy.getAsciiArtPath()) << std::endl;

			// walka / ucieczka
            bool escaped = false;
            int turn = 1;

			// petla walki
            while (player.isAlive() && enemy.isAlive())
            {
                std::cout << "\n--- Tura " << turn << " ---\n";
                std::cout << "1) Atak\n2) Ucieczka\n> ";

                int choice;
                std::cin >> choice;

                if (choice == 2)
                {
                    if (std::rand() % 2 == 0)
                    { // 50%
                        std::cout << "Ucieczka udana!\n";
                        escaped = true;
                        break;
                    }
                    else
                    {
                        std::cout << "Ucieczka nieudana! Przeciwnik atakuje.\n";
                        enemy.attack(&player);
                        std::cout << "Player HP: " << player.getHealth() << "\n";
                        turn++;
                        continue;
                    }
                }

				// normalny atak po wyborze 1 
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

			// koniec walki - wyniki
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
                saveReportSimple("report.txt", report);

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
                saveReportSimple("report.txt", report);
            }

            // wygrana (5 walk)
            if (wins >= WIN_CONDITION)
            {
                std::string report;
                report += "=== RPG REPORT ===\n";
                report += "Result: Victory (5 wins)\n";
                report += "Wins: " + std::to_string(wins) + "/" + std::to_string(WIN_CONDITION) + "\n";
                report += "Player HP: " + std::to_string(player.getHealth()) + "\n";
                saveReportSimple("report.txt", report);

                std::cout << "\nGRATULACJE! Wygrales gre (5 wygranych).\n";
                std::cout << "Report saved to report.txt\n";
                return;
            }

            // menu (po walce lub ucieczce)
            while (true)
            {
                std::cout << "\n1) Wyrusz dalej\n2) Zakoncz droge\n> ";
                int after;
                std::cin >> after;

                if (after == 1)
                    break; // dalej odpali sie kolejne spotkanie
                if (after == 2)
                {
                    std::string report;
                    report += "=== RPG REPORT ===\n";
                    report += "Result: Abandoned (player ended the journey)\n";
                    report += "Wins: " + std::to_string(wins) + "/" + std::to_string(WIN_CONDITION) + "\n";
                    report += "Player HP: " + std::to_string(player.getHealth()) + "\n";
                    saveReportSimple("report.txt", report);

                    std::cout << "\nZakonczyles droge.\n";
                    std::cout << "Report saved to report.txt\n";
                    return;
                }
            }
        }
    }
}

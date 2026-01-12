#include <fstream>
#include <ctime>
void FileManager::saveReport(
    const std::string& playerName,
    int playerHP,
    int enemiesDefeated
) {
    std::ofstream file("report.txt", std::ios::app);
    if (!file.is_open()) return;
    std::time_t now = std::time(nullptr);
    file << "===== GAME REPORT =====\n";
    file << "Player: " << playerName << "\n";
    file << "HP left: " << playerHP << "\n";
    file << "Enemies defeated: " << enemiesDefeated << "\n";
    file << "Time: " << std::ctime(&now);
    file << "=======================\n\n";
    file.close();
}



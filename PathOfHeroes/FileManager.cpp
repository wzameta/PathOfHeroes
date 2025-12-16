#include "FileManager.h"
#include "fstream"

std::vector<std::string> FileManager::loadEnemies(const std::string& path) {
	std::ifstream file(path);
	std::vector<std::string> lines;
	std::string line;
	while (std::getline(file, line)) {
		lines.push_back(line);
	}
	return lines;
}


void FileManager::saveReport(const std::string& path, const std::string& text) {
	std::ofstream file(path);
	file << text;
}









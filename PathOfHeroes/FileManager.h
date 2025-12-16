#pragma once
#include <string>
#include <vector>

class FileManager {
public:
	static std::vector<std::string> loadEnemies(const std::string& path);
	static void saveReport(const std::string& path, const std::string& text);
};






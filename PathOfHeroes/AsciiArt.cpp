#include "AsciiArt.h"
#include <fstream>
#include <sstream>

std::string AsciiArt::load(const std::string& path) {
    std::ifstream file(path);
    std::ostringstream ss;
    ss << file.rdbuf();
    if (!file.is_open()) {
        return "ASCII FILE NOT FOUND\n";
    }
    return ss.str();
}

#include "AsciiArt.h"
#include <fstream>
#include <sstream>

std::string AsciiArt::load(const std::string &path)
{
    std::ifstream file(path);

    std::ostringstream ss;
    if (!file.is_open())
    {
        return "ASCII FILE NOT FOUND\n";
    }
    ss << file.rdbuf();
    return ss.str();
}

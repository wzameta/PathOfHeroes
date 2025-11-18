#pragma once
#include <string>

// Przedmiot: nazwa, typ i wartoœæ
class Item {
public:
    std::string name;
    std::string type;
    int value;
    Item() = default;
    Item(const std::string& n, const std::string& t, int v)
        : name(n), type(t), value(v) {
    }
};

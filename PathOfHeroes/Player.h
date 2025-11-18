#pragma once
#include "Character.h"
#include "Item.h"
#include <vector>

// Klasa Player dziedziczy po Character.1
class Player : public Character {
    int xp;
    std::vector<Item> inventory;
public:
    Player(const std::string& n);

    void attack(Character& target) override;
    void addXp(int amount);
    void addItem(const Item& it);
    void useItem(int idx);
};

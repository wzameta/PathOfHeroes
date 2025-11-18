#include "Player.h"
#include <iostream>

Player::Player(const std::string& n)
    : Character(n, 100, 15, 3), xp(0) {
}

void Player::attack(Character& target) {
    int damage = atk; // prosty model: zadawane obra¿enia = si³a ataku
    target.takeDamage(damage);
    std::cout << name << " atakuje " << target.getName()
        << " za " << damage << " obrazen.\n";
}

void Player::addXp(int amount) { xp += amount; }
void Player::addItem(const Item& it) { inventory.push_back(it); }

void Player::useItem(int idx) {
    if (idx < 0 || idx >= static_cast<int>(inventory.size())) {
        std::cout << "Brak przedmiotu na tym miejscu.\n";
        return;
    }
    const Item& it = inventory[idx];
    if (it.type == "heal") {
        hp += it.value;
        std::cout << "Uzywasz " << it.name << ". +" << it.value << " HP\n";
    }
    // usuwamy uzyty przedmiot
    inventory.erase(inventory.begin() + idx);
}

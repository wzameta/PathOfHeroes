#include "Player.h"
#include <iostream>

Player::Player(int hp, int ap) : Character(hp, ap), level(1), experience(0) {}

void Player::takeDamage(int dmg) {
    health -= dmg;
    if (health < 0)
        health = 0;
}

void Player::attack(Character* target) {
    int dmg = attackPower;

    // 10% szansy na krytyk
    if (rand() % 10 == 0) {
        dmg *= 2;
    }

    target->takeDamage(dmg);
}

void Player::gainExp(int amount) {
    experience += amount;
    if (experience >= 100) {
        level++;
        experience = 0;
		maxHealth += 10;
        health = maxHealth;
    }
}

int Player::getLevel() const {
    return level;
}


void Player::debug() {
    std::cout << "Player HP: " << health << std::endl;
}



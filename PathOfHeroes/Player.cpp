#include "Player.h"
#include <iostream>

Player::Player(int hp, int ap) : Character(hp, ap), level(1), experience(0) {}

void Player::takeDamage(int dmg) {
    health -= dmg;
    if (health < 0) health = 0;
}

void Player::attack(Character* target) {
    target->takeDamage(attackPower);
}

void Player::debug() {
    std::cout << "Player HP: " << health << std::endl;
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


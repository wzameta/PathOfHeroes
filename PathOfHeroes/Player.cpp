#include "Player.h"
#include <iostream>

Player::Player(int hp, int ap) : Character(hp, ap) {}

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



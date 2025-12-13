#include "Player.h"

Player::Player(int hp, int ap) : Character(hp, ap) {}

void Player::takeDamage(int dmg) {
    health -= dmg;
}

void Player::attack(Character* target) {
    target->takeDamage(attackPower);
}




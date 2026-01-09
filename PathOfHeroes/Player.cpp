#include "Player.h"

Player::Player(int hp, int ap) : Character(hp, ap) {}

void Player::takeDamage(int dmg) {
    health -= dmg;
    if (health < 0)
        health = 0;
}


void Player::attack(Character* target) {
    target->takeDamage(attackPower);
}




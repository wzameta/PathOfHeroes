#include "Enemy.h"

Enemy::Enemy(int hp, int ap) : Character(hp, ap) {}

void Enemy::attack(Character* target) {
    target->takeDamage(attackPower);
}

void Enemy::takeDamage(int dmg) {
    health -= dmg;
    if (health < 0) health = 0;
}

void Enemy::debug() {}



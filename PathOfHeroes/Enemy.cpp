#include "Enemy.h"
#include <iostream>

Enemy::Enemy() : Character("Enemy", 10, 2, 0), xpValue(0) {}

Enemy::Enemy(const std::string& n, int h, int a, int d, int xp)
    : Character(n, h, a, d), xpValue(xp) {
}

void Enemy::attack(Character& target) {
    int damage = atk;
    target.takeDamage(damage);
    std::cout << name << " atakuje " << target.getName()
        << " za " << damage << " obrazen.\n";
}

int Enemy::getXp() const { return xpValue; }

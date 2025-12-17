#include "Enemy.h"

Enemy::Enemy(int hp, int ap, EnemyType t) : Character(hp, ap), type(t) {}

EnemyType Enemy::getType() const {
    return type;
}

std::string Enemy::getTypeAsString() const {
    switch (type) {
    case EnemyType::Goblin:   return "Goblin";
    case EnemyType::Orc:      return "Orc";
    case EnemyType::Skeleton: return "Skeleton";
    case EnemyType::Demon:    return "Demon";
    default:                  return "Unknown";
    }
}

void Enemy::attack(Character* target) {
    target->takeDamage(attackPower);
}

void Enemy::takeDamage(int dmg) {
    health -= dmg;
    if (health < 0) health = 0;
}

void Enemy::debug() {}







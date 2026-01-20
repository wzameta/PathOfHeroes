#include "Enemy.h"

Enemy::Enemy(int hp, int ap, EnemyType t) : Character(hp, ap), type(t)
{
}


std::string Enemy::getAsciiArtPath() const
{
    switch (type)
    {
    case EnemyType::Goblin:
        return "ascii/goblin.txt";
    case EnemyType::Orc:
        return "ascii/orc.txt";
    case EnemyType::Skeleton:
        return "ascii/skeleton.txt";
    default:
        return "";
    }
}

void Enemy::attack(Character *target)
{
    target->takeDamage(attackPower);
}

void Enemy::takeDamage(int dmg)
{
    health -= dmg;
    if (health < 0)
        health = 0;
}



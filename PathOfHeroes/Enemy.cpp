#include "Enemy.h"

Enemy::Enemy(int hp, int ap, EnemyType t) : Character(hp, ap), type(t)
{
}

EnemyType Enemy::getType() const
{
    return type;
}

std::string Enemy::getTypeAsString() const
{
    switch (type)
    {
    case EnemyType::Goblin:
        return "Goblin";
    case EnemyType::Orc:
        return "Orc";
    case EnemyType::Skeleton:
        return "Skeleton";
    default:
        return "Unknown";
    }
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

void Enemy::setHealth(int hp)
{
    health = hp;
}

void Enemy::setAttackPower(int ap)
{
    attackPower = ap;
}

void Enemy::debug()
{
}

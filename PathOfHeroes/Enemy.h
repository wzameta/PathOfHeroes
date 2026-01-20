#pragma once
#include "Character.h"
#include <string>

enum class EnemyType
{
    Goblin,
    Orc,
    Skeleton,
};

class Enemy : public Character
{
    EnemyType type;

  public:
    Enemy(int hp, int ap, EnemyType t);
    EnemyType getType() const;

    std::string getTypeAsString() const;
    std::string getAsciiArtPath() const;

    void attack(Character *target) override;
    void takeDamage(int dmg) override;
    void setHealth(int hp);
    void setAttackPower(int ap);

    void debug();
};

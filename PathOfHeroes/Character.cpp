#include "Character.h"

Character::Character(int hp, int ap) : health(hp), attackPower(ap)
{
}

int Character::getHealth() const
{
    return health;
}

int Character::getAttackPower() const
{
    return attackPower;
}

bool Character::isAlive() const
{
    return health > 0;
}

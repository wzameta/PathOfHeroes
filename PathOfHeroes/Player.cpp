#include "Player.h"
#include <iostream>

Player::Player(int hp, int ap) : Character(hp, ap)
{
}

void Player::takeDamage(int dmg)
{
    health -= dmg;
    if (health < 0)
        health = 0;
}

void Player::attack(Character *target)
{
    int dmg = attackPower;

    // 10% szansy na krytyk
    if (rand() % 10 == 0)
    {
        dmg *= 2;
    }

    target->takeDamage(dmg);
}

void Player::debug()
{
    std::cout << "Player HP: " << health << std::endl;
}

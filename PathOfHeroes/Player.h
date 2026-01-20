#pragma once
#include "Character.h"

class Player : public Character
{
  public:
    Player(int hp, int ap);
    void attack(Character *target) override;
    void takeDamage(int dmg) override;
    void debug();
};

#pragma once

class Character
{
  protected:
    int health, attackPower, maxHealth;

  public:
    Character(int hp, int ap);
    virtual ~Character() = default;

    int getHealth() const;
    int getAttackPower() const;
    bool isAlive() const;
    void heal(int amount);

    virtual void attack(Character *target) = 0;
    virtual void takeDamage(int dmg) = 0;
};

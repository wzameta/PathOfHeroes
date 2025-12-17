#pragma once


class Character {
protected:
	int health, attackPower;
public:
	Character(int hp, int ap);
	virtual ~Character() = default;

	int getHealth() const;
	int getAttackPower() const;
	bool isAlive() const;

	virtual void attack(Character* target) = 0;
	virtual void takeDamage(int dmg) = 0;
};



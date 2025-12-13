#pragma once


class Character {
protected:
	int health, attackPower;
public:
	Character(int hp, int ap);
	virtual ~Character() = default;

	int getHealth() const;
	int getAttackPower() const;
};



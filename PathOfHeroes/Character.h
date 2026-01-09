#pragma once


class Character {
protected:
	int health, attackPower;
public:
	Character(int hp, int ap);
	virtual ~Character() = default;

	int getHealth() const;
	int getAttackPower() const;

	


	virtual void attack(Character* target) = 0;
	virtual void takeDamage(int dmg) = 0;

	
	bool isAlive() const;


};





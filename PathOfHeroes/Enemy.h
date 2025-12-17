#pragma once
#include "Character.h"

class Enemy : public Character {
public:
	Enemy(int hp, int ap);
	void attack(Character* target) override;
	void takeDamage(int dmg) override;
	void debug();
};







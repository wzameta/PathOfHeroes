#include "Character.h"

Character::Character(int hp, int ap) : health(hp), maxHealth(hp), attackPower(ap) {}

int Character::getHealth() const {
	return health;
}

int Character::getAttackPower() const {
	return attackPower;
}

bool Character::isAlive() const {
	return health > 0;
}

bool Character::isDead() const {
	return health <= 0;
}

void Character::heal(int amount) {
	health += amount;
	if (health > maxHealth) health = maxHealth;
}

bool Character::isAlive() const {
		return health > 0;
}









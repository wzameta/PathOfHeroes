#include "Character.h"
#include <algorithm>

Character::Character(const std::string& n, int h, int a, int d)
    : name(n), hp(h), atk(a), def(d) {
}

void Character::takeDamage(int dmg) {
    // zmniejszamy zadane obrazenia o wartosc obrony
    int effective = std::max(0, dmg - def);
    hp = std::max(0, hp - effective);
}

bool Character::isAlive() const { return hp > 0; }
const std::string& Character::getName() const { return name; }
int Character::getHp() const { return hp; }

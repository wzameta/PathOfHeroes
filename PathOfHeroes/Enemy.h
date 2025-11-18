#pragma once
#include "Character.h"

class Enemy : public Character {
    int xpValue;
public:
    Enemy();
    Enemy(const std::string& n, int h, int a, int d, int xp);
    void attack(Character& target) override;
    int getXp() const;
};

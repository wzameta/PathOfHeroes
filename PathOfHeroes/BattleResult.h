#pragma once
#include <string>

struct BattleResult {
    std::string enemyName;
    int playerHpAfter;
    int expGained;
    bool levelUp;
};

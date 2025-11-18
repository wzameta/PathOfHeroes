#pragma once
#pragma once
#include <string>

// Klasa abstrakcyjna: baza dla gracza i przeciwników.
// Zawiera podstawowe pola (name, hp, atk, def) i metody.
class Character {
protected:
    std::string name;
    int hp;
    int atk;
    int def;
public:
    Character(const std::string& n, int h, int a, int d);
    virtual ~Character() = default;

    // metoda czysto wirtualna (ka¿da klasa pochodna musi j¹ zaimplementowaæ)
    virtual void attack(Character& target) = 0;

    // zmniejsza HP, uwzglêdnia obronê (def)
    virtual void takeDamage(int dmg);

    bool isAlive() const;
    const std::string& getName() const;
    int getHp() const;
};

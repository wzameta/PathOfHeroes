#include <iostream>
#include "Player.h"
#include "Enemy.h"

int main()
{
	Player player(100, 20);
	Enemy enemy(60, 10);

	std::cout << "Health - Player: " << player.getHealth() << ", Enemy: " << enemy.getHealth() << std::endl;

	std::cout << "The battle begins! Player attacks Enemy!" << std::endl;
	player.attack(&enemy);

	std::cout << "Health - Enemy: " << enemy.getHealth() << std::endl;

	std::cout << "\nEnemy attacks Player!\n";
	enemy.attack(&player);

	std::cout << "Health - Player: " << player.getHealth() << std::endl;


	return 0;
}


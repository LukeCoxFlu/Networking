#include "person.h"
#include <stdlib.h>
#include <thread>
#include <iostream>
#include <time.h> 


void person::initCombat(person& enemy)
{
	while (true)
	{
		if (health <= 0)
		{
			break;
		}
		srand(time(0));
		int randomSleepTime = rand() % 2000 + 1;
		std::this_thread::sleep_for(std::chrono::milliseconds(randomSleepTime));
		std::cout << "Attack from " << playerName << std::endl;
		
		int randomDamage = rand() % 10 + 1;
		enemy.health -= (int)((float)enemy.defence / 100 * randomDamage);

		if (enemy.health <= 0)
		{
			std::cout << enemy.playerName << " Is DEAD." << "Ya did it on " << health << std::endl;
			break;
		}
	}
}

int person::getHealth()
{
	return health;
}

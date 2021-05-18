#include "game.h"
#include <iostream>
game::game(int clientID, int numCars)
{
	_checkpoints[0] = { 300, 610 };
	_checkpoints[1] = { 1270,430 };
	_checkpoints[2] = { 1380,2380 };
	_checkpoints[3] = { 1900,2460 };
	_checkpoints[4] = { 1970,1700 };
	_checkpoints[5] = { 2550,1680 };
	_checkpoints[6] = { 2560,3150 };
	_checkpoints[7] = { 500, 3300 };

	_playerCarID = clientID;
	for (int i = 0; i < numCars; i++)
	{
		if (i == _playerCarID)
		{
			_CARS.push_back(new playerCar(i, _startingPos));
		}
		else 
		{
			_CARS.push_back(new car(i, _startingPos));
		}
	}


}

game::~game()
{
	for (car* car : _CARS)
	{
		delete car;
	}
}

void game::update()
{
	for (car* car : _CARS) car->move();
}

car* game::getPlayerCar()
{
	return _CARS[_playerCarID];
}

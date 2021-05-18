#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include "car.h"
#include "playerCar.h"

class game
{
private:

	sf::Vector2f _checkpoints[8]; //Hardcoded
	sf::Vector2f _startingPos = { 300, 1700 }; //Hardcoded
	int _playerCarID; 

public:
	std::vector<car*> _CARS;
	game(int clientID, int numCars);
	~game();

	void update();
	car* getPlayerCar();
};


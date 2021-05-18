#pragma once
#include "car.h"

struct playerMovement
{
	bool Up = 0, Right = 0, Down = 0, Left = 0;
};


class playerCar : public car
{
private:
	playerMovement currentPlayerMovement;
	float maxSpeed = 12.0;
	float acc = 0.2, dec = 0.3;
	float turnSpeed = 0.08;

public:
	playerCar(int carID, sf::Vector2f startingPoint) : car(carID, startingPoint) {}
	void move() override;
	void getOffset(int& offsetX, int& offsetY);
};


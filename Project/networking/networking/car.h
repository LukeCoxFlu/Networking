#pragma once
#include "SFML/Graphics.hpp"

class car
{	
protected:
	int carID;
public:
	sf::Vector2f pos;
	float speed{2}, angle{ 0 };
	car(int carID, sf::Vector2f startingPoint);
	virtual void move();
	virtual void getOffset(int& offsetX, int& offsetY) {};
};


#include "car.h"

car::car(int carid, sf::Vector2f startingPoint)
{
    carID = carid;
    pos.x = startingPoint.x + carID * 50;
    pos.y = startingPoint.y + carID * 80;
    speed = 7 + carID;
}

void car::move()
{
}

#include "playerCar.h"
#include <SFML/Graphics.hpp>

using namespace sf;
void playerCar::move()
{
    currentPlayerMovement.Down = 0;
    currentPlayerMovement.Up = 0;
    currentPlayerMovement.Right = 0;
    currentPlayerMovement.Left = 0;
    if (Keyboard::isKeyPressed(Keyboard::W)) currentPlayerMovement.Up = 1;
    if (Keyboard::isKeyPressed(Keyboard::D)) currentPlayerMovement.Right = 1;
    if (Keyboard::isKeyPressed(Keyboard::S)) currentPlayerMovement.Down = 1;
    if (Keyboard::isKeyPressed(Keyboard::A)) currentPlayerMovement.Left = 1;


    //car movement * HOW && WORKS LIKE THIS
    if (currentPlayerMovement.Up && speed < maxSpeed)
    {
        if (speed < 0)  speed += dec;
        else  speed += acc;
    }
    if (currentPlayerMovement.Down && speed > -maxSpeed)
    {
        if (speed > 0) speed -= dec;
        else  speed -= acc;
    }
    if (!currentPlayerMovement.Up && !currentPlayerMovement.Down)
    {
        if (speed - dec > 0) speed -= dec;
        else if (speed + dec < 0) speed += dec;
        else speed = 0;
    }

    if (currentPlayerMovement.Right && speed != 0)  angle += turnSpeed * speed / maxSpeed;
    if (currentPlayerMovement.Left && speed != 0)   angle -= turnSpeed * speed / maxSpeed;

    pos.x += sin(angle) * speed;
    pos.y -= cos(angle) * speed;
}

void playerCar::getOffset(int& offsetX, int& offsetY)
{
    if (pos.x > 320) offsetX = pos.x - 320;
    if (pos.y > 240) offsetY = pos.y - 240;
}

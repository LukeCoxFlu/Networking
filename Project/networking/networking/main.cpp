#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "playerCar.h"
#include "game.h"
#include <map>
#include <conio.h>
#include <string>
#include <iostream>
#include <thread>
using namespace sf;

// TODO: use checkpoint to make sure we are on the track.
// Slow speed when not on the track.
// TODO: Stay within the limit of the map.
// TODO: Don't show white at bottom/right.



int main()
{
   
    sf::IpAddress ip = sf::IpAddress::getLocalAddress();
    sf::UdpSocket socket;
    sf::Packet packet;
    char buffer[2000];
    std::string connectionMessage = "Connected to a new Client";

    unsigned short port;

    std::cout << "Set port number: ";
    std::cin >> port;
    
    socket.bind(port);

    std::string theServersIP;
    std::cout << "Enter Server IP: ";
    std::cin >> theServersIP;

    sf::IpAddress sendIP(ip);

    socket.send(connectionMessage.c_str(), connectionMessage.length() + 1, sendIP, 2000);

    std::size_t recieved;
    while (true)
    {
        sf::IpAddress tempIP;
        unsigned short tempPort;
        socket.receive(buffer, sizeof(buffer), recieved, tempIP, tempPort);
        if (recieved > 0)
        {
            std::cout << "Recieved: " << buffer << std::endl;
        }
    }

//---------------------------------------------Boiler Plat SFML----------------------------------------------- Client Side
    RenderWindow app(VideoMode(640, 480), "Car Racing Game!");
    app.setFramerateLimit(60);
    Texture t1, t2;
    t1.loadFromFile("images/background.png");
    t2.loadFromFile("images/car.png");
    t1.setSmooth(true);
    t2.setSmooth(true);
    Sprite sBackground(t1), sCar(t2);
    sBackground.scale(2, 2);
    sCar.setOrigin(22, 22);
//------------------------------------------------------------------------------------------------------------



    game* clientGame = new game(0,5);


    while (app.isOpen())
    {
        Event e;
        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed)
                app.close();
        }
        
        clientGame->update();
        int offsetX = 0 , offsetY = 0;
        clientGame->getPlayerCar()->getOffset(offsetX, offsetY);
        


        //Setting And Resetting Background
        app.clear(Color::White);
        sBackground.setPosition(-offsetX, -offsetY);
        app.draw(sBackground);

        //Drawing Cars
        Color colors[10] = { Color::Red, Color::Green, Color::Magenta, Color::Blue, Color::White };
        int colourCount = 0;
        for (car* car : clientGame->_CARS)
        {
            sCar.setPosition(car->pos.x - offsetX, car->pos.y - offsetY);
            sCar.setRotation(car->angle * 180 / 3.141593);
            sCar.setColor(colors[colourCount]);
            colourCount++;
            app.draw(sCar);
        }
        app.display();
    }

    delete clientGame;
    return 0;
}

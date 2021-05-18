#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include<SFML/Audio.hpp>
#include<string>
#include<vector>
#include<iostream>
#include<conio.h>
class conections
{
public:
	sf::IpAddress clientIP;
	unsigned short port;
	unsigned int CarNumber;
    conections(sf::IpAddress ip, unsigned short nport, int ID)
    {
        clientIP = ip; port = nport; CarNumber = ID;
    }

};

int carCount = 0;

int main()
{
	std::vector<conections> clients;

    sf::IpAddress ip = sf::IpAddress::getLocalAddress();
    sf::UdpSocket socket;
    sf::Packet packet;
    char buffer[2000];
    std::size_t recieved;
    std::string connectionMessage = "Connected to a new Client";

    unsigned short port;

    std::cout << "Set port number: ";
    std::cin >> port;

    socket.bind(port);

    //socket.setBlocking(false);

    bool stillLookingForClients = true;
    while (stillLookingForClients)
    {
        sf::IpAddress rIP;
        unsigned short newPort;

        socket.receive(buffer, sizeof(buffer), recieved, rIP, newPort);
        if (recieved > 0)
        {
            clients.push_back(conections(rIP, newPort, carCount));
            carCount++;
            int yeet = 1;
            std::cin >> yeet;
            stillLookingForClients = yeet;
        }
    }

    while (true)
    {
        std::string text = "s";
        std::getline(std::cin, text);

        for (conections client : clients)
        {
            std::cout << client.CarNumber;
            socket.send(text.c_str(), text.length() + 1, client.clientIP, client.port);
        }
    }
}
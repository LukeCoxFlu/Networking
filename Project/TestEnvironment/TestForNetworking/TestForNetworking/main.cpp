#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include "person.h"
#include "circularBoundingBuffer.h"
#include "SFML/Network.hpp"


#define PRINT std::cout

enum connectionType
{
	client,
	Server
};


void print(int i)
{
	i ++;
	std::cout << i << std::endl;
}

static bool s_Finished = false;




//void workerThreadExec()
//{
//	using namespace std::literals::chrono_literals;
//	while (!s_Finished)
//	{
//		std::cout << "Yeet";
//		std::this_thread::sleep_for(1s);
//	}
//}

void funcExample_ThreadAsynchronisity()
{
	int numThreads = 8;
	std::vector<std::thread> threads;

	for (int i = 0; i < numThreads; i++)
	{
		threads.push_back(std::thread([]()
			{
				std::cout << "Hello from thread" << std::this_thread::get_id() << std::endl;
			}));
	}

	for (auto& x : threads)
	{
		x.join();
	}

}



void funcExample_HighLevelCircularBoundingBuffer()
{
	circularBoundingBuffer<int, 5> CBB;

	for (int i = 1; i < 8; i++)
	{
		if (!CBB.write(i)) std::cout << "\nFailed To Write\n";
		else CBB.statusUpdate();
	}

	CBB.printBuffer();

	int temp = 0;
	for (int i = 1; i < 4; i++)
	{
		if (!CBB.read(temp))
		{
			PRINT << "\nno more left\n";
		}
		else
		{
			PRINT << "\nJust Read: " << temp << std::endl;
		}
	}
	CBB.statusUpdate();

	//THIS IS ACTUALLY THE COOLEST
	PRINT << "\nPrinting Now...\n";
	CBB.BUFFER_FOREACH(
		[](int& value, int index)
		{
			int v = value;
			v++;
			std::cout << v << std::endl;
		});
	PRINT << "\nPrinting Now...\n";
	CBB.BUFFER_FOREACH(
		[](int& value,int index)
		{
			std::cout << index << ": "<< value << std::endl;
		});
}

void func_RolfVDan()
{
	person person1("Rolfor", 100, 50);
	person person2("Gaurd Dan", 165, 90);

	std::thread attackThread1{ &person::initCombat,
								&person1,
								std::ref(person2) };
	std::thread attackThread2{ &person::initCombat,
								&person2,
								std::ref(person1) };

	attackThread1.join();
	attackThread2.join();
}

void func_FunctioningConsumerProducerMutexAndConditions()
{
	circularBoundingBuffer<int, 5> CBB;

	std::thread c1{ &circularBoundingBuffer<int, 5>::consumerThread,
					&CBB,
					0 };
	std::thread c2{ &circularBoundingBuffer<int, 5>::consumerThread,
					&CBB,
					1 };
	std::thread c3{ &circularBoundingBuffer<int, 5>::consumerThread, &CBB, 2 };

	std::thread p1{ &circularBoundingBuffer<int, 5>::producerThread,
					&CBB,
					0 };

	std::thread p2{ &circularBoundingBuffer<int, 5>::producerThread,
					&CBB,
					1 };

	std::this_thread::sleep_for(std::chrono::milliseconds(10000));

	CBB.printBuffer();


	c1.join();
	c2.join();
	c3.join();
	p1.join();
	p2.join();
}

void func_NetworkingStart()
{
	sf::TcpSocket listeningSocket;
	connectionType v_connectionType;
	unsigned short listenPort = 4444;
	std::string text = "Connected To: ";

	char buffer[2000];
	size_t recieved;

	sf::IpAddress ip = sf::IpAddress::getLocalAddress();

	PRINT << "Enter (1) for Server, and (0) for client\n";

	int temp;
	std::cin >> temp;
	v_connectionType = static_cast<connectionType>(temp);

	if (v_connectionType == connectionType::client)
	{
		listeningSocket.connect(ip, listenPort);

		text += "Client\n";


	}
	else if (v_connectionType == connectionType::Server)
	{
		sf::TcpListener listener;

		listener.listen(listenPort);
		listener.accept(listeningSocket);

		text += "Server\n";
	}


	bool hasDisconnect = false;
	if (v_connectionType == connectionType::client)
	{
		while (true)
		{
			text = "";
			std::string myMessage;
			std::cin >> myMessage;

			text += myMessage;
			listeningSocket.send(text.c_str(), text.length() + 1);

		}

	}
	else if (v_connectionType == connectionType::Server)
	{
		
		while (!hasDisconnect)
		{
			sf::Socket::Status temp = listeningSocket.receive(buffer, sizeof(buffer), recieved);

			if (temp == sf::Socket::Status::Disconnected)
			{
				hasDisconnect = true;
				PRINT << "OOF Client at port " << listenPort << " Has  DISCONNECTED\n";
				sf::TcpListener listener;

				listener.listen(listenPort);
				if (listener.accept(listeningSocket) == sf::Socket::Status::Done)
				{
					hasDisconnect = false;
				}
			}
			else
			{
				PRINT << buffer << std::endl;
			}
		}

	}

	system("pause");
}

int main()
{
	func_NetworkingStart();

	return 0;
}
#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include "person.h"
#include "circularBoundingBuffer.h"

#define PRINT std::cout


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

void funcExample_ThreadsWithClasses()
{
	person gary(100);

	std::thread damageThread{ &person::calculateCurrentHealth,  //parsing a function pointer to the function we want to thread
							&gary,								//Parsing this
							15,									// Var 1
							enum_DamageType::PENIS,				// Var 2
							3148124 };							// Var 3

	damageThread.join();
	std::cout << gary.getHealth();
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

int main()
{
	funcExample_HighLevelCircularBoundingBuffer();

	return 0;
}
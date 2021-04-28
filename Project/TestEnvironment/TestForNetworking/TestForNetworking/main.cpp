#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include "person.h"

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

int main()
{
	funcExample_ThreadsWithClasses();

	return 0;
}
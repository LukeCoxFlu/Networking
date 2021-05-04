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

int main()
{
	func_FunctioningConsumerProducerMutexAndConditions();
	
	return 0;
}
#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include <mutex>

template<typename BUFFER_TYPE, int BUFFER_SIZE>
class circularBoundingBuffer
{
private:
	BUFFER_TYPE buffer[BUFFER_SIZE];
	unsigned int writeHead{ 0 };
	unsigned int readHead{ 0 };
	bool IsFull = false;
	bool IsEmpty = true;

	//Networking
	std::mutex m_lock;

	std::condition_variable not_full;
	std::condition_variable not_empty;

	//Increments the head by one if the head is at the max size then wrap around
	void increment(unsigned int& head) {head = (head + 1) % BUFFER_SIZE;}
	bool isBufferEmpty()
	{
		if ((readHead == writeHead) && !IsFull) return true;
		else return false;
	}

public:
	void statusUpdate() const
	{
		std::cout << "The Head is at Index: " << writeHead << ".\n The Tail is at Index: " << readHead << ".\n IsFull =" << IsFull << std::endl;
	}

	void printBuffer()
	{
		if (isBufferEmpty()) std::cout << "Buffer Empty";
		else
		{
			std::cout << "\nPrinting Buffer...\n";
			//The buffer offset is created by finding the amount of items in the list and adding it to readHead
			int Offset = readHead + (BUFFER_SIZE - abs(readHead - writeHead));
			for (int i = readHead; i < Offset; i++)
			{
				//Then All you need to do % Buffer Size
				std::cout << std::to_string(buffer[i % BUFFER_SIZE]) << std::endl;
			}
		}
	}

	//Bool For Fail
	bool write(BUFFER_TYPE data)
	{
		std::unique_lock<std::mutex> unique_L(m_lock);
		not_full.wait(unique_L, [&]() {return !IsFull; });

		if (IsFull) return false;
		else
		{
			buffer[writeHead] = data;
			increment(writeHead);
			IsEmpty = false;

			if (writeHead == readHead) IsFull = true;
			not_empty.notify_one();
			return true;
		}
	}

	//takes in a data of the type and changes it to the read
	bool read(BUFFER_TYPE& data)
	{
		std::unique_lock<std::mutex> unique_l(m_lock);

		not_empty.wait(unique_l, [&]() {return !IsEmpty; });


		if (IsEmpty) return false;
		else
		{
			data = buffer[readHead];
			increment(readHead);

			if (isBufferEmpty()) IsEmpty = true;
			IsFull = false;
		}

		not_full.notify_one();
		return true;
	}

	//Functions outside after, template declaration (Current and Index)
	void BUFFER_FOREACH(void(*FUNC_BUFFERLOOP)(BUFFER_TYPE&, int))
	{
		if (isBufferEmpty()) std::cout << "Buffer Empty";
		else
		{
			//The buffer offset is created by finding the amount of items in the list and adding it to readHead
			int Offset = readHead + (BUFFER_SIZE - abs(readHead - writeHead));
			for (int i = readHead; i < Offset; i++)
			{
				//Then All you need to do % Buffer Size and call the function pointer
				int location = i % BUFFER_SIZE;
				int index = i - readHead;
				FUNC_BUFFERLOOP(buffer[location], index);
			}
		}
	}
	//Did work with Function pointers past through Template. Take a look at variadic template, http://www.cplusplus.com/forum/general/209696/

	void consumerThread(int id)
	{
		for (int i = 0; i < 50; i++)
		{
			BUFFER_TYPE value = 0;
			if(!read(value)) std::cout << "Something has gone terrable wrong";

			std::cout << "Consumer: " << id << " fetched " << value << std::endl;

			std::this_thread::sleep_for(std::chrono::milliseconds(250));
		}
	}

	void producerThread(int id)
	{
		for (int i = 0; i < 75; i++)
		{
			if (!write(i)) std::cout << "Something has gone terrable wrong";

			std::cout << "Producer: " << id << " produced " << i << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
	}
};



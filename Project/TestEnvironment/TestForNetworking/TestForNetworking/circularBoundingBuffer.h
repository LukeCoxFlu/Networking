#pragma once
#include <iostream>
#include <string>
#include <cmath>

template<typename BUFFER_TYPE, int BUFFER_SIZE>
class circularBoundingBuffer
{
private:
	BUFFER_TYPE buffer[BUFFER_SIZE];
	unsigned int writeHead{ 0 };
	unsigned int readHead{ 0 };
	bool IsFull = false;

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
		if (IsFull) return false;
		else
		{
			buffer[writeHead] = data;
			increment(writeHead);
			if (writeHead == readHead) IsFull = true;
			return true;
		}
	}

	//takes in a data of the type and changes it to the read
	bool read(BUFFER_TYPE& data)
	{
		if (isBufferEmpty()) return false;
		else
		{
			data = buffer[readHead];
			increment(readHead);
			IsFull = false;
		}
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

};

